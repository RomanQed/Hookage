//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_HOOKMANAGER_H
#define HOOKLOADER_HOOKMANAGER_H

#include <unordered_map>
#include <memory>
#include "Hook.h"
#include "io/Closable.h"

using std::unordered_map;
using std::shared_ptr;

class HookManager : public Closable {
public:
    [[nodiscard]] virtual const unordered_map<void *, shared_ptr<Hook>> &getHooks() = 0;

    virtual shared_ptr<Hook> addHook(void *function, void *hook) = 0;

    virtual shared_ptr<Hook> deleteHook(void *function) = 0;
};


#endif //HOOKLOADER_HOOKMANAGER_H
