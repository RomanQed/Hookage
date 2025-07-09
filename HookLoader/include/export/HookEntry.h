//
// Created by Roman on 08.08.2023.
//

#ifndef HOOKLOADER_HOOKENTRY_H
#define HOOKLOADER_HOOKENTRY_H


struct HookEntry {
    const char *lib;
    const char *name;
    void *hook;
};


#endif //HOOKLOADER_HOOKENTRY_H
