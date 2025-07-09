//
// Created by Roman on 16.08.2023.
//

#include "base/BaseLoggerFactory.h"
#include "base/FileOutputStream.h"
#include "base/BaseLogger.h"
#include <stdexcept>

using std::make_shared;
using std::runtime_error;

BaseLoggerFactory::BaseLoggerFactory(const string &directory, LogLevel level) {
    this->directory = directory;
    this->level = level;
}

shared_ptr<Logger> BaseLoggerFactory::create(const char *name) {
    auto path = directory;
    auto end = path[path.length() - 1];
    if (end != '/' && end != '\\') {
        path += '/';
    }
    path += name;
    auto *file = fopen(path.c_str(), "w");
    if (file == nullptr) {
        throw runtime_error("Cannot create log file");
    }
    auto stream = make_shared<FileOutputStream>(file);
    return make_shared<BaseLogger>(stream, level);
}
