//
// Created by Roman on 06.08.2023.
//

#ifndef HOOKLIB_DYNAMICLIBRARY_H
#define HOOKLIB_DYNAMICLIBRARY_H

#include <memory>

using std::shared_ptr;

class DynamicLibrary {
public:
    static shared_ptr<DynamicLibrary> load(const char *path, int flag);

    void *getFunction(const char *name);

    void close();

    bool isClosed();

private:
    explicit DynamicLibrary(void *handle);

    void checkHandle();

    void *handle;
};

#endif //HOOKLIB_DYNAMICLIBRARY_H
