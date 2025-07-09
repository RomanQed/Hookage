//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_LOADEVENTIMPL_H
#define HOOKLOADER_LOADEVENTIMPL_H


#include "events/LoadEvent.h"
#include "DLLEventImpl.h"

class LoadEventImpl : public LoadEvent, public DLLEventImpl {
public:
    [[nodiscard]] shared_ptr<HookManager> getHookManager() override;

    [[nodiscard]] shared_ptr<LoggerFactory> getLoggerFactory() override;

    [[nodiscard]] shared_ptr<ConsoleFactory> getConsoleFactory() const noexcept override;

    [[nodiscard]] shared_ptr<ConfigReader> getConfigReader() const noexcept override;

    [[nodiscard]] HINSTANCE getInstance() const noexcept override;

    [[nodiscard]] DWORD getReason() const noexcept override;

    void setHookManager(const shared_ptr<HookManager> &value);

    void setLoggerFactory(const shared_ptr<LoggerFactory> &value);

    void setConsoleFactory(const shared_ptr<ConsoleFactory> &value);

    void setConfigReader(const shared_ptr<ConfigReader> &value);

private:
    shared_ptr<HookManager> manager;
    shared_ptr<LoggerFactory> loggerFactory;
    shared_ptr<ConsoleFactory> consoleFactory;
    shared_ptr<ConfigReader> reader;
};


#endif //HOOKLOADER_LOADEVENTIMPL_H
