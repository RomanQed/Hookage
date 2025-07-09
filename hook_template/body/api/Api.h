//
// Created by Roman on 08.08.2023.
//

#ifndef HOOKLOADER_API_H
#define HOOKLOADER_API_H

#include <vector>
#include "HookEntry.h"
#include "events/LoadEvent.h"
#include "events/UnloadEvent.h"

using std::vector;

typedef void (__cdecl *DescriptorLoader)(void *data);

// Descriptor
#define HOOK(LIB_NAME, FUNC_NAME)
#define DESCRIPTOR_NAME "loadDescriptor"
#define DESCRIPTOR extern "C" __declspec(dllexport) __cdecl void loadDescriptor(void *data)
#define DESCRIPTOR_ADD(LIB_NAME, FUNC_NAME, HOOK_PTR) ((vector<HookEntry> *) data)->push_back({LIB_NAME, FUNC_NAME, (void *) HOOK_PTR})

// Events
typedef void (__cdecl *LoadEventFunc)(LoadEvent &);

typedef void (__cdecl *UnloadEventFunc)(UnloadEvent &);

#define LOAD_EVENT_NAME "onLoad"
#define UNLOAD_EVENT_NAME "onUnload"

#define ON_LOAD(EVENT) extern "C" __declspec(dllexport) __cdecl void onLoad(LoadEvent &EVENT)
#define ON_UNLOAD(EVENT) extern "C" __declspec(dllexport) __cdecl void onUnload(UnloadEvent &EVENT)

#endif //HOOKLOADER_API_H
