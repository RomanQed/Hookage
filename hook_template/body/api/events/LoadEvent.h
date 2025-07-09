//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_LOADEVENT_H
#define HOOKLOADER_LOADEVENT_H

#include <windows.h>
#include "console/ConsoleFactory.h"
#include "logger/LoggerFactory.h"
#include "hooks/HookManager.h"
#include "DLLEvent.h"
#include "config/ConfigReader.h"


class LoadEvent : public DLLEvent {
public:
    [[nodiscard]] virtual shared_ptr<HookManager> getHookManager() = 0;

    [[nodiscard]] virtual shared_ptr<LoggerFactory> getLoggerFactory() = 0;

    [[nodiscard]] virtual shared_ptr<ConsoleFactory> getConsoleFactory() const noexcept = 0;

    [[nodiscard]] virtual shared_ptr<ConfigReader> getConfigReader() const noexcept = 0;
};


#endif //HOOKLOADER_LOADEVENT_H
