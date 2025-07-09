//
// Created by Roman on 06.08.2023.
//
#include <windows.h>
#include <memory>
#include "Define.h"
#include "util/Utils.h"
#include "impl/UnloadEventImpl.h"
#include "Api.h"
#include "impl/LoadEventImpl.h"
#include <filesystem>

using namespace std;

#define MAIN_CONFIG "loader.cfg"

BOOL attach(HINSTANCE instance, DWORD reason);

BOOL detach(HINSTANCE instance, DWORD reason);

#include <iostream>

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID ptr) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            return attach(instance, reason);

        case DLL_PROCESS_DETACH:
            return detach(instance, reason);

        default:
            break;
    }

    return true;
}

using dirIterator = std::filesystem::recursive_directory_iterator;

void loadDll(const string &name, LoadEvent &event, vector<shared_ptr<DynamicLibrary>> &libs);

BOOL attach(HINSTANCE instance, DWORD reason) {
    try {
        // Init
        Utils::init(MAIN_CONFIG);
        Utils::getLogger()->log(LogLevel::INFO, "Initialization started");
        // Prepare event
        LoadEventImpl event;
        event.setInstance(instance);
        event.setReason(reason);
        event.setHookManager(Utils::getHookManager());
        event.setConfigReader(Utils::getConfigReader());
        event.setConsoleFactory(Utils::getConsoleFactory());
        event.setLoggerFactory(Utils::getLoggerFactory());
        // Load libs
        Utils::getLogger()->log(LogLevel::INFO, "Loading dlls");
        const auto &hookPath = Utils::getConfig().getField(HOOK_DIRECTORY);
        auto libs = Utils::getLoadedLibs();
        for (const auto &entry: dirIterator(hookPath)) {
            if (!entry.exists()) {
                throw runtime_error("Hook file does not exists");
            }
            loadDll(entry.path().string(), event, libs);
        }
        // Check for necessary to resume main thread
        auto threadId = Utils::getParentThreadId();
        if (threadId < 0) {
            Utils::getLogger()->log(LogLevel::INFO, "Thread id not found, skip");
        } else {
            Utils::getLogger()->log(LogLevel::INFO, "Trying to open thread for thread id: " + to_string(threadId));
            auto handle = OpenThread(THREAD_SUSPEND_RESUME, false, threadId);
            if (handle == nullptr) {
                throw runtime_error("Cannot open thread");
            }
            if (FAILED(ResumeThread(handle))) {
                throw runtime_error("Cannot resume thread, error code " + to_string(GetLastError()));
            }
            Utils::getLogger()->log(LogLevel::INFO, "Thread resumed");
        }

        Utils::getLogger()->log(LogLevel::INFO, "Initialization completed");
    } catch (exception &e) {
        Utils::getLogger()->log(LogLevel::FAIL, e.what());
        Utils::getLogger()->close();
        return false;
    }
    return true;
}

void loadDll(const string &name, LoadEvent &event, vector<shared_ptr<DynamicLibrary>> &libs) {
    // Load lib
    Utils::getLogger()->log(LogLevel::INFO, "Loading lib " + name);
    auto lib = DynamicLibrary::load(name.c_str(), 0);
    // Get loader
    auto loader = (DescriptorLoader) lib->getFunction(DESCRIPTOR_NAME);
    if (loader == nullptr) {
        throw runtime_error("Descriptor not found");
    }
    vector<HookEntry> descriptor;
    loader(&descriptor);
    // Invoke event
    auto func = (LoadEventFunc) lib->getFunction(LOAD_EVENT_NAME);
    if (func != nullptr) {
        func(event);
    }
    // Install all hooks
    Utils::getLogger()->log(LogLevel::INFO, "Install hooks for " + name);
    auto manager = Utils::getHookManager();
    for (const auto &entry: descriptor) {
        Utils::getLogger()->log(LogLevel::INFO,
                                string("Install hook for lib = ") + entry.lib + ", proc = " + entry.name);
        auto module = GetModuleHandleA(entry.lib);
        if (module == nullptr) {
            throw runtime_error("Unknown module name");
        }
        auto proc = (void *) GetProcAddress(module, entry.name);
        if (proc == nullptr) {
            throw runtime_error("Unknown proc name");
        }
        manager->addHook(proc, entry.hook);
        Utils::getLogger()->log(LogLevel::INFO, "Hook installed successfully");
    }
    // Add lib to list
    libs.push_back(lib);
}

BOOL detach(HINSTANCE instance, DWORD reason) {
    try {
        // Prepare event
        Utils::getLogger()->log(LogLevel::INFO, "Preparing the closing of the dll");
        UnloadEventImpl event;
        event.setInstance(instance);
        event.setReason(reason);
        event.setHookManager(Utils::getHookManager());
        event.setConfigReader(Utils::getConfigReader());
        auto libs = Utils::getLoadedLibs();
        Utils::getLogger()->log(LogLevel::INFO, "Invoking unload events");
        // Invoke events
        for (const auto &lib: libs) {
            auto func = (UnloadEventFunc) lib->getFunction(UNLOAD_EVENT_NAME);
            if (func == nullptr) {
                continue;
            }
            func(event);
        }
        // Remove hooks
        Utils::getLogger()->log(LogLevel::INFO, "Destroying hooks");
        Utils::getHookManager()->close();
        // Close libs
        Utils::getLogger()->log(LogLevel::INFO, "Unloading dlls");
        for (const auto &lib: libs) {
            lib->close();
        }
    } catch (exception &e) {
        Utils::getLogger()->log(LogLevel::FAIL, e.what());
        Utils::getLogger()->close();
        return false;
    }
    Utils::getLogger()->close();
    return true;
}
