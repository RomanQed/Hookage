//
// Created by Roman on 27.08.2023.
//
#include "Util.h"
#include <stdexcept>

using std::runtime_error;

#define KERNEL_32 L"kernel32.dll"
#define MAX_FILENAME 2048

string getCurrentDirectory() {
    char buffer[MAX_FILENAME];
    if (FAILED(GetCurrentDirectoryA(MAX_FILENAME, buffer))) {
        throw runtime_error("Cannot get current directory");
    }
    return {buffer};
}

void inject(DWORD processId, const char *lib) {
    // Open process handle
    auto process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (process == nullptr) {
        throw runtime_error("Cannot open process");
    }

    // Find kernel32 module
    auto kernel = GetModuleHandleW(KERNEL_32);
    if (kernel == nullptr) {
        CloseHandle(process);
        throw runtime_error("Cannot open kernel32");
    }

    // Find LoadLibraryA func addr
    auto loadLibraryFunc = static_cast<void *>(GetProcAddress(kernel, "LoadLibraryA"));
    if (loadLibraryFunc == nullptr) {
        CloseHandle(process);
        CloseHandle(kernel);
        throw runtime_error("Cannot find LoadLibraryA");
    }

    // Allocate memory
    auto memory = VirtualAllocEx(process,
                                 nullptr,
                                 strlen(lib),
                                 MEM_RESERVE | MEM_COMMIT,
                                 PAGE_READWRITE);
    if (memory == nullptr) {
        CloseHandle(process);
        CloseHandle(kernel);
        throw runtime_error("Cannot allocate memory for target process");
    }

    // Write dll name to process
    int wrote = WriteProcessMemory(process, memory, lib, strlen(lib), nullptr);
    if (wrote == 0) {
        CloseHandle(process);
        CloseHandle(kernel);
        VirtualFreeEx(process, memory, 0, MEM_RELEASE);
        throw runtime_error("Cannot write to target process memory");
    }
    // Create remote thread
    auto injected = CreateRemoteThread(process,
                                       nullptr,
                                       0,
                                       static_cast<LPTHREAD_START_ROUTINE>(loadLibraryFunc),
                                       memory,
                                       0,
                                       nullptr);
    // Check result
    if (injected == nullptr) {
        CloseHandle(process);
        CloseHandle(kernel);
        CloseHandle(injected);
        VirtualFreeEx(process, memory, 0, MEM_RELEASE);
        throw runtime_error("Cannot attach remote thread to target process");
    }
    // Close opened process handle
    CloseHandle(process);
}

PROCESS_INFORMATION runProcess(const char *command, DWORD flags) {
    PROCESS_INFORMATION ret{};
    STARTUPINFO info{};
    auto result = CreateProcessA(
            nullptr,
            const_cast<LPSTR>(command),
            nullptr,
            nullptr,
            false,
            flags,
            nullptr,
            nullptr,
            &info,
            &ret
    );
    if (FAILED(result)) {
        CloseHandle(ret.hProcess);
        throw runtime_error("Cannot run process");
    }
    return ret;
}
