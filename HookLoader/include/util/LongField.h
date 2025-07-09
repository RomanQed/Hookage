//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_LONGFIELD_H
#define HOOKLOADER_LONGFIELD_H


#include "config/ConfigField.hpp"

class LongField : public ConfigField<ssize_t> {
public:
    explicit LongField(const string &name) : ConfigField<ssize_t>(name) {}

    ssize_t fromString(const string &value) override;

    string toString(const ssize_t &&value) override;
};


#endif //HOOKLOADER_LONGFIELD_H
