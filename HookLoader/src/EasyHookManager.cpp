//
// Created by Roman on 16.08.2023.
//

#include "easyhooks/EasyHookManager.h"
#include "easyhooks/EasyHook64.h"
#include <stdexcept>

using std::runtime_error;
using std::make_shared;
using std::lock_guard;

const unordered_map<void *, shared_ptr<Hook>> &EasyHookManager::getHooks() {
    return body;
}

shared_ptr<Hook> EasyHookManager::addHook(void *function, void *hook) {
    lock_guard<mutex> guard(lock);
    if (body.find(function) != body.end()) {
        throw runtime_error("Found hook duplicate");
    }
    auto toAdd = make_shared<EasyHook64>(function, hook);
    body[function] = toAdd;
    toAdd->install();
    return toAdd;
}

shared_ptr<Hook> EasyHookManager::deleteHook(void *function) {
    lock_guard<mutex> guard(lock);
    auto found = body.find(function);
    if (found == body.end()) {
        return {};
    }
    auto ret = found->second;
    ret->uninstall();
    body.erase(function);
    return ret;
}

bool EasyHookManager::isClosed() {
    return this->closed;
}

void EasyHookManager::close() {
    lock_guard<mutex> guard(lock);
    for (const auto &entry: body) {
        entry.second->uninstall();
    }
    body.clear();
    this->closed = true;
}
