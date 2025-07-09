//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_UNLOADEVENTIMPL_H
#define HOOKLOADER_UNLOADEVENTIMPL_H


#include "events/UnloadEvent.h"
#include "DLLEventImpl.h"

class UnloadEventImpl : public DLLEventImpl, public UnloadEvent {
public:
    [[nodiscard]] shared_ptr<HookManager> getHookManager() override;

    [[nodiscard]] shared_ptr<ConfigReader> getConfigReader() override;

    [[nodiscard]] HINSTANCE getInstance() const noexcept override;

    [[nodiscard]] DWORD getReason() const noexcept override;

    void setHookManager(const shared_ptr<HookManager> &value);

    void setConfigReader(const shared_ptr<ConfigReader> &value);

private:
    shared_ptr<HookManager> manager;
    shared_ptr<ConfigReader> reader;
};


#endif //HOOKLOADER_UNLOADEVENTIMPL_H
