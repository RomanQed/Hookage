//
// Created by Roman on 15.08.2023.
//

#include "easyhooks/EasyHook64.h"
#include "export/hooks/HookException.h"
#include <string_view>

using std::wstring_view;

EasyHook64::EasyHook64(void *function, void *hook) {
    this->function = function;
    this->hook = hook;
}

void *EasyHook64::getFunction() noexcept {
    return function;
}

void *EasyHook64::getHook() noexcept {
    return hook;
}

void *EasyHook64::getHandle() noexcept {
    return &handle;
}

static void checkStatus(NTSTATUS status) {
    if (SUCCEEDED(status)) {
        return;
    }
    throw HookException(RtlGetLastError(), {RtlGetLastErrorString()});
}

void EasyHook64::install() {
    static ULONG entries[1] = {0};
    checkStatus(LhInstallHook(function, hook, nullptr, &handle));
    checkStatus(LhSetExclusiveACL(entries, 1, &handle));
}

void EasyHook64::uninstall() {
    checkStatus(LhUninstallHook(&handle));
    checkStatus(LhWaitForPendingRemovals());
}
