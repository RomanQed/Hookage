//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_BASECONSOLE_H
#define HOOKLOADER_BASECONSOLE_H

#include "export/console/Console.h"


class BaseConsole : public Console {
public:
    string read() override;

    int read(const char *format, ...) override;

    void write(const string &value) override;

    void write(const string_view &value) override;

    int write(const char *format, ...) override;
};


#endif //HOOKLOADER_BASECONSOLE_H
