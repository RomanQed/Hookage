//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_HOOK_H
#define HOOKLOADER_HOOK_H


class Hook {
public:
    [[nodiscard]] virtual void *getFunction() noexcept = 0;

    [[nodiscard]] virtual void *getHook() noexcept = 0;

    [[nodiscard]] virtual void *getHandle() noexcept = 0;

    virtual void install() = 0;

    virtual void uninstall() = 0;
};


#endif //HOOKLOADER_HOOK_H
