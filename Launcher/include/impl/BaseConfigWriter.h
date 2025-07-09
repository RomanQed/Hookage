//
// Created by Roman on 27.08.2023.
//

#ifndef HOOKLAUNCHER_BASECONFIGWRITER_H
#define HOOKLAUNCHER_BASECONFIGWRITER_H


#include "config/ConfigWriter.h"

class BaseConfigWriter : public ConfigWriter {
public:
    void write(const char *name, const Config &config) override;
};


#endif //HOOKLAUNCHER_BASECONFIGWRITER_H
