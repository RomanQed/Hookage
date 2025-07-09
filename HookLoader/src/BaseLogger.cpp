//
// Created by Roman on 15.08.2023.
//

#include "base/BaseLogger.h"
#include <iostream>
#include <cstdarg>

using std::to_string;

BaseLogger::BaseLogger(const shared_ptr<OutputStream> &stream, LogLevel level) {
    this->stream = stream;
    this->logLevel = level;
}

LogLevel BaseLogger::getLogLevel() {
    return this->logLevel;
}

void BaseLogger::writeLogHeader(LogLevel level) {
    stream->write('[');
    string_view name = levelToString(level);
    if (name.empty()) {
        stream->write('?');
    } else {
        stream->write(name);
    }
    stream->write(']');
}

void BaseLogger::log(LogLevel level, const string &value) {
    if (level < logLevel) {
        return;
    }
    writeLogHeader(level);
    stream->write(value);
    stream->write('\n');
}

void BaseLogger::log(LogLevel level, const string_view &value) {
    if (level < logLevel) {
        return;
    }
    writeLogHeader(level);
    stream->write(value);
    stream->write('\n');
}

void BaseLogger::log(LogLevel level, int value) {
    if (level < logLevel) {
        return;
    }
    writeLogHeader(level);
    stream->write(to_string(value));
    stream->write('\n');
}

int BaseLogger::log(LogLevel level, const char *format, ...) {
    if (level < logLevel) {
        return -1;
    }
    writeLogHeader(level);
    va_list args;
    va_start(args, format);
    int ret = stream->write(format, args);
    va_end(args);
    stream->write('\n');
    return ret;
}

bool BaseLogger::isClosed() {
    return this->stream->isClosed();
}

void BaseLogger::close() {
    this->stream->close();
}
