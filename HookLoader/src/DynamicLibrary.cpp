//
// Created by Roman on 06.08.2023.
//
#include "util/DynamicLibrary.h"
#include <stdexcept>

using std::runtime_error;
using std::make_shared;

#if defined(linux) \
 || defined(__linux) \
 || defined (__unix__) \
 || (defined (__APPLE__) && defined (__MACH__))
#define POSIX_DLL
#endif

#if defined(_WIN32) || defined (_WIN64)
#define WIN_DLL
#endif

#if defined(WIN_DLL)

#include <windows.h>

static const char *GetWinError() {
    static char buffer[22];
    lltoa(GetLastError(), buffer, 10);
    return buffer;
}

#define LIB_LOAD(filename, flag) LoadLibraryExA(filename, nullptr, flag)
#define LIB_ERROR GetWinError
#define LIB_LOAD_FUNC(handle, symbol) (void *) GetProcAddress((HMODULE) handle, symbol)
#define LIB_CLOSE(handle) (FreeLibrary((HMODULE) handle))
#elif defined(POSIX_DLL)
#include <dlfcn.h>

#define LIB_LOAD(filename, flag) dlopen(filename, flag)
#define LIB_ERROR dlerror
#define LIB_LOAD_FUNC(handle, symbol) dlsym(handle, symbol)
#define LIB_CLOSE(handle) dlclose(handle)
#else
#error UNKNOWN DLL LIBRARY
#endif


void DynamicLibrary::checkHandle() {
    if (this->handle == nullptr) {
        throw runtime_error("Library closed");
    }
}

shared_ptr<DynamicLibrary> DynamicLibrary::load(const char *path, int flag) {
    void *handle = LIB_LOAD(path, flag);
    if (handle == nullptr) {
        throw runtime_error(LIB_ERROR());
    }
    return shared_ptr<DynamicLibrary>(new DynamicLibrary(handle));
}

DynamicLibrary::DynamicLibrary(void *handle) {
    this->handle = handle;
}

void *DynamicLibrary::getFunction(const char *name) {
    checkHandle();
    return LIB_LOAD_FUNC(this->handle, name);
}

bool DynamicLibrary::isClosed() {
    return this->handle == nullptr;
}

void DynamicLibrary::close() {
    checkHandle();
    if (!LIB_CLOSE(this->handle)) {
        throw runtime_error(LIB_ERROR());
    }
    this->handle = nullptr;
}
