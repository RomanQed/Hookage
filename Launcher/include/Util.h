//
// Created by Roman on 27.08.2023.
//

#ifndef HOOKLAUNCHER_UTIL_H
#define HOOKLAUNCHER_UTIL_H

#include <windows.h>
#include <string>

using std::string;

string getCurrentDirectory();

void inject(DWORD pid, const char *lib);

PROCESS_INFORMATION runProcess(const char *command, DWORD flags);

#endif //HOOKLAUNCHER_UTIL_H
