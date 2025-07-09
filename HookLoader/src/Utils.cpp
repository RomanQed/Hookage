//
// Created by Roman on 25.08.2023.
//

#include "util/Utils.h"
#include "easyhooks/EasyHookManager.h"
#include "base/BaseConfigReader.h"
#include "winapi/WinConsoleFactory.h"
#include "util/LongField.h"
#include "Define.h"
#include "base/BaseLoggerFactory.h"

using std::make_shared;

vector<shared_ptr<DynamicLibrary>> Utils::libs;
Config Utils::config;
long long Utils::threadId;
shared_ptr<HookManager> Utils::manager;
shared_ptr<LoggerFactory> Utils::loggerFactory;
shared_ptr<ConsoleFactory> Utils::consoleFactory;
shared_ptr<ConfigReader> Utils::reader;
shared_ptr<Logger> Utils::logger;

void Utils::init(const char *name) {
    // Init basic factories
    manager = make_shared<EasyHookManager>();
    reader = make_shared<BaseConfigReader>();
    consoleFactory = make_shared<WinConsoleFactory>();
    // Read main config
    config = reader->read(name);
    // Read process and thread ids
    threadId = config.getField(LongField(THREAD_ID), (long long) -1);
    // Read logger params
    auto directory = config.getField(LOG_DIRECTORY);
    auto level = (LogLevel) config.getField(LongField(LOG_LEVEL), (long long) LogLevel::INFO);
    loggerFactory = make_shared<BaseLoggerFactory>(directory, level);
    logger = loggerFactory->create(LOG_FILE);
}

Config &Utils::getConfig() {
    return config;
}

shared_ptr<HookManager> Utils::getHookManager() {
    return manager;
}

shared_ptr<LoggerFactory> Utils::getLoggerFactory() {
    return loggerFactory;
}

shared_ptr<ConsoleFactory> Utils::getConsoleFactory() {
    return consoleFactory;
}

shared_ptr<ConfigReader> Utils::getConfigReader() {
    return reader;
}

long long Utils::getParentThreadId() {
    return threadId;
}

shared_ptr<Logger> Utils::getLogger() {
    return logger;
}

vector<shared_ptr<DynamicLibrary>> &Utils::getLoadedLibs() {
    return libs;
}
