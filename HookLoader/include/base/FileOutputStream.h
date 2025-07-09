//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_FILEOUTPUTSTREAM_H
#define HOOKLOADER_FILEOUTPUTSTREAM_H


#include "export/io/OutputStream.h"
#include "util/FileStream.h"

class FileOutputStream : public OutputStream, public FileStream {
public:
    explicit FileOutputStream(FILE *file) : FileStream(file) {}

    void write(int value) override;

    void write(const char *value, size_t length) override;

    void write(const string_view &value) override;

    void write(const string &value) override;

    int write(const char *format, va_list args) override;

    void close() override;

    bool isClosed() override;
};


#endif //HOOKLOADER_FILEOUTPUTSTREAM_H
