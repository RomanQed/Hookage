//
// Created by Roman on 24.08.2023.
//

#include "impl/UnloadEventImpl.h"

shared_ptr<HookManager> UnloadEventImpl::getHookManager() {
    return this->manager;
}

shared_ptr<ConfigReader> UnloadEventImpl::getConfigReader() {
    return this->reader;
}

void UnloadEventImpl::setHookManager(const shared_ptr<HookManager> &value) {
    this->manager = value;
}

void UnloadEventImpl::setConfigReader(const shared_ptr<ConfigReader> &value) {
    this->reader = value;
}

HINSTANCE UnloadEventImpl::getInstance() const noexcept {
    return DLLEventImpl::getInstance();
}

DWORD UnloadEventImpl::getReason() const noexcept {
    return DLLEventImpl::getReason();
}
