//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_FILESTREAM_H
#define HOOKLOADER_FILESTREAM_H

#include <cstdio>
#include <mutex>
#include "export/io/Closable.h"

using std::mutex;

class FileStream : public Closable {
protected:
    explicit FileStream(FILE *file);

    void checkFile();

public:
    ~FileStream() override;

    void close() override;

    bool isClosed() override;

protected:
    mutex lock;
    FILE *file;
};


#endif //HOOKLOADER_FILESTREAM_H
