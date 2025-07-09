//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_UNLOADEVENT_H
#define HOOKLOADER_UNLOADEVENT_H

#include "DLLEvent.h"
#include "hooks/HookManager.h"
#include "config/ConfigReader.h"

class UnloadEvent : public DLLEvent {
public:
    [[nodiscard]] virtual shared_ptr<HookManager> getHookManager() = 0;

    [[nodiscard]] virtual shared_ptr<ConfigReader> getConfigReader() = 0;
};

#endif //HOOKLOADER_UNLOADEVENT_H
