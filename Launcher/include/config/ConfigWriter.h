//
// Created by Roman on 27.08.2023.
//

#ifndef HOOKLAUNCHER_CONFIGWRITER_H
#define HOOKLAUNCHER_CONFIGWRITER_H


#include "Config.hpp"

class ConfigWriter {
public:
    virtual void write(const char *name, const Config &config) = 0;
};


#endif //HOOKLAUNCHER_CONFIGWRITER_H
