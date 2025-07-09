//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_OUTPUTSTREAM_H
#define HOOKLOADER_OUTPUTSTREAM_H

#include <string>
#include <string_view>
#include "Closable.h"

using std::string;
using std::string_view;

class OutputStream : public Closable {
public:
    virtual void write(int value) = 0;

    virtual void write(const char *value, size_t length) = 0;

    virtual void write(const string_view &value) = 0;

    virtual void write(const string &value) = 0;

    virtual int write(const char *format, va_list args) = 0;
};

#endif //HOOKLOADER_OUTPUTSTREAM_H
