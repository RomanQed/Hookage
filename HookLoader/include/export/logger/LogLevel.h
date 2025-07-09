//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_LOGLEVEL_H
#define HOOKLOADER_LOGLEVEL_H

#include <string_view>

using std::string_view;

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    FAIL = 2
};

string_view levelToString(LogLevel level);

#endif //HOOKLOADER_LOGLEVEL_H
