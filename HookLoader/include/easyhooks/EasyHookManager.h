//
// Created by Roman on 16.08.2023.
//

#ifndef HOOKLOADER_EASYHOOKMANAGER_H
#define HOOKLOADER_EASYHOOKMANAGER_H

#include <mutex>
#include "export/hooks/HookManager.h"

using std::mutex;

class EasyHookManager : public HookManager {
public:
    const unordered_map<void *, shared_ptr<Hook>> &getHooks() override;

    shared_ptr<Hook> addHook(void *function, void *hook) override;

    shared_ptr<Hook> deleteHook(void *function) override;

    bool isClosed() override;

    void close() override;

private:
    mutex lock;
    bool closed = false;
    unordered_map<void *, shared_ptr<Hook>> body;
};


#endif //HOOKLOADER_EASYHOOKMANAGER_H
