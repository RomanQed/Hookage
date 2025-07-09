//
// Created by Roman on 16.08.2023.
//

#ifndef HOOKLOADER_CONFIGREADER_H
#define HOOKLOADER_CONFIGREADER_H


#include "Config.hpp"

class ConfigReader {
public:
    [[nodiscard]] virtual Config read(const char *name) = 0;
};


#endif //HOOKLOADER_CONFIGREADER_H
