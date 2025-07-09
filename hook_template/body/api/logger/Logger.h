//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_LOGGER_H
#define HOOKLOADER_LOGGER_H

#include "LogLevel.h"
#include "io/Closable.h"
#include <string>
#include <string_view>

using std::string;
using std::string_view;

class Logger : public Closable {
public:
    [[nodiscard]] virtual LogLevel getLogLevel() = 0;

    virtual void log(LogLevel level, const string &value) = 0;

    virtual void log(LogLevel level, const string_view &value) = 0;

    virtual void log(LogLevel level, int value) = 0;

    virtual int log(LogLevel level, const char *format, ...) = 0;
};


#endif //HOOKLOADER_LOGGER_H
