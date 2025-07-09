//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_FILEINPUTSTREAM_H
#define HOOKLOADER_FILEINPUTSTREAM_H


#include "export/io/InputStream.h"
#include "util/FileStream.h"

class FileInputStream : public InputStream, public FileStream {
public:
    explicit FileInputStream(FILE *file) : FileStream(file) {}

    int read() override;

    string readLine() override;

    int read(const char *format, va_list args) override;

    void close() override;

    bool isClosed() override;
};

#endif //HOOKLOADER_FILEINPUTSTREAM_H
