//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_LOGGERFACTORY_H
#define HOOKLOADER_LOGGERFACTORY_H

#include "Logger.h"
#include "io/OutputStream.h"
#include <memory>

using std::shared_ptr;

class LoggerFactory {
public:
    [[nodiscard]] virtual shared_ptr<Logger> create(const char *name) = 0;
};

#endif //HOOKLOADER_LOGGERFACTORY_H
