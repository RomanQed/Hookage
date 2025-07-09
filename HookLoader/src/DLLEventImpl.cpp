//
// Created by Roman on 24.08.2023.
//

#include "impl/DLLEventImpl.h"

HINSTANCE DLLEventImpl::getInstance() const noexcept {
    return this->instance;
}

DWORD DLLEventImpl::getReason() const noexcept {
    return this->reason;
}

void DLLEventImpl::setInstance(HINSTANCE value) {
    DLLEventImpl::instance = value;
}

void DLLEventImpl::setReason(DWORD value) {
    DLLEventImpl::reason = value;
}
