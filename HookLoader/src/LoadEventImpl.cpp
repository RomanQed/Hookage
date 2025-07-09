//
// Created by Roman on 24.08.2023.
//

#include "impl/LoadEventImpl.h"

shared_ptr<HookManager> LoadEventImpl::getHookManager() {
    return this->manager;
}

shared_ptr<LoggerFactory> LoadEventImpl::getLoggerFactory() {
    return this->loggerFactory;
}

shared_ptr<ConsoleFactory> LoadEventImpl::getConsoleFactory() const noexcept {
    return this->consoleFactory;
}

shared_ptr<ConfigReader> LoadEventImpl::getConfigReader() const noexcept {
    return this->reader;
}

void LoadEventImpl::setHookManager(const shared_ptr<HookManager> &value) {
    this->manager = value;
}

void LoadEventImpl::setLoggerFactory(const shared_ptr<LoggerFactory> &value) {
    this->loggerFactory = value;
}

void LoadEventImpl::setConsoleFactory(const shared_ptr<ConsoleFactory> &value) {
    this->consoleFactory = value;
}

void LoadEventImpl::setConfigReader(const shared_ptr<ConfigReader> &value) {
    this->reader = value;
}

HINSTANCE LoadEventImpl::getInstance() const noexcept {
    return DLLEventImpl::getInstance();
}

DWORD LoadEventImpl::getReason() const noexcept {
    return DLLEventImpl::getReason();
}
