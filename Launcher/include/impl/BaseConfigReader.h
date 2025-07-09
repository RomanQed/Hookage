//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_BASECONFIGREADER_H
#define HOOKLOADER_BASECONFIGREADER_H


#include "config/ConfigReader.h"

class BaseConfigReader : public ConfigReader {
public:
    Config read(const char *name) override;
};


#endif //HOOKLOADER_BASECONFIGREADER_H
