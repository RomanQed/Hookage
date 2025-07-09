//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_EASYHOOK_H
#define HOOKLOADER_EASYHOOK_H

#include "easyhook.h"
#include "export/hooks/Hook.h"

class EasyHook64 : public Hook {
public:
    EasyHook64(void *function, void *hook);

    void *getFunction() noexcept override;

    void *getHook() noexcept override;

    void *getHandle() noexcept override;

    void install() override;

    void uninstall() override;

private:
    HOOK_TRACE_INFO handle = {nullptr};
    void *hook;
    void *function;
};

#endif //HOOKLOADER_EASYHOOK_H
