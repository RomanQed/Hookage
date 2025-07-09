//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_CONSOLE_H
#define HOOKLOADER_CONSOLE_H

#include "io/Closable.h"
#include "io/InputStream.h"
#include "io/OutputStream.h"

class Console : public Closable {
public:
    virtual InputStream &getInput() = 0;

    virtual OutputStream &getOutput() = 0;

    virtual string read() = 0;

    virtual int read(const char *format, ...) = 0;

    virtual void write(const string &value) = 0;

    virtual void write(const string_view &value) = 0;

    virtual int write(const char *format, ...) = 0;
};

#endif //HOOKLOADER_CONSOLE_H
