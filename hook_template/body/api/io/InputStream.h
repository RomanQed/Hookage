//
// Created by Roman on 06.08.2023.
//

#ifndef HOOKLOADER_INPUTSTREAM_H
#define HOOKLOADER_INPUTSTREAM_H

#include <string>
#include "Closable.h"

using std::string;

class InputStream : public Closable {
public:
    virtual int read() = 0;

    virtual string readLine() = 0;

    virtual int read(const char *format, va_list args) = 0;
};


#endif //HOOKLOADER_INPUTSTREAM_H
