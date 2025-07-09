//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_DOUBLEFIELD_H
#define HOOKLOADER_DOUBLEFIELD_H


#include "config/ConfigField.hpp"

class DoubleField : public ConfigField<double> {
public:
    double fromString(const string &value) override;

    string toString(const double &&value) override;
};


#endif //HOOKLOADER_DOUBLEFIELD_H
