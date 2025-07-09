//
// Created by Roman on 16.08.2023.
//

#ifndef HOOKLOADER_BASELOGGERFACTORY_H
#define HOOKLOADER_BASELOGGERFACTORY_H

#include <string>
#include "export/logger/LoggerFactory.h"

using std::string;

class BaseLoggerFactory : public LoggerFactory {
public:
    BaseLoggerFactory(const string &directory, LogLevel level);

    shared_ptr<Logger> create(const char *name) override;

private:
    LogLevel level;
    string directory;
};


#endif //HOOKLOADER_BASELOGGERFACTORY_H
