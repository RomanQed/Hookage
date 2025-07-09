//
// Created by Roman on 15.08.2023.
//

#include "base/BaseConsole.h"
#include <cstdarg>

string BaseConsole::read() {
    return this->getInput().readLine();
}

int BaseConsole::read(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = this->getInput().read(format, args);
    va_end(args);
    return ret;
}

void BaseConsole::write(const string &value) {
    this->getOutput().write(value);
}

void BaseConsole::write(const string_view &value) {
    this->getOutput().write(value);
}

int BaseConsole::write(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = this->getOutput().write(format, args);
    va_end(args);
    return ret;
}
