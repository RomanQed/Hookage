//
// Created by Roman on 25.08.2023.
//

#ifndef HOOKLOADER_UTILS_H
#define HOOKLOADER_UTILS_H

#include <memory>
#include <vector>
#include "hooks/HookManager.h"
#include "logger/LoggerFactory.h"
#include "console/ConsoleFactory.h"
#include "config/ConfigReader.h"
#include "DynamicLibrary.h"

using std::shared_ptr;
using std::vector;

class Utils {
public:
    static void init(const char *name);

    static Config &getConfig();

    static long long getParentThreadId();

    static shared_ptr<Logger> getLogger();

    static shared_ptr<HookManager> getHookManager();

    static shared_ptr<LoggerFactory> getLoggerFactory();

    static shared_ptr<ConsoleFactory> getConsoleFactory();

    static shared_ptr<ConfigReader> getConfigReader();

    static vector<shared_ptr<DynamicLibrary>> &getLoadedLibs();

private:
    static vector<shared_ptr<DynamicLibrary>> libs;
    static Config config;
    static long long threadId;
    static shared_ptr<HookManager> manager;
    static shared_ptr<LoggerFactory> loggerFactory;
    static shared_ptr<ConsoleFactory> consoleFactory;
    static shared_ptr<ConfigReader> reader;
    static shared_ptr<Logger> logger;
};

#endif //HOOKLOADER_UTILS_H
