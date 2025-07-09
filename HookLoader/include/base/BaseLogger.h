//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_BASELOGGER_H
#define HOOKLOADER_BASELOGGER_H


#include "export/logger/LoggerFactory.h"

class BaseLogger : public Logger {
public:
    BaseLogger(const shared_ptr<OutputStream> &stream, LogLevel level);

    LogLevel getLogLevel() override;

    void log(LogLevel level, const string &value) override;

    void log(LogLevel level, const string_view &value) override;

    void log(LogLevel level, int value) override;

    int log(LogLevel level, const char *format, ...) override;

    bool isClosed() override;

    void close() override;

private:
    LogLevel logLevel;
    shared_ptr<OutputStream> stream;

    void writeLogHeader(LogLevel level);
};


#endif //HOOKLOADER_BASELOGGER_H
