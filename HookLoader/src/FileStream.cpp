//
// Created by Roman on 07.08.2023.
//

#include <stdexcept>
#include "util/FileStream.h"

using std::runtime_error;
using std::lock_guard;

FileStream::FileStream(FILE *file) {
    this->file = file;
    checkFile();
}

FileStream::~FileStream() {
    fclose(file);
}

void FileStream::close() {
    lock_guard<mutex> guard(lock);
    if (file == nullptr) {
        return;
    }
    fclose(file);
    file = nullptr;
}

void FileStream::checkFile() {
    if (file == nullptr) {
        throw runtime_error("Null file ptr");
    }
}

bool FileStream::isClosed() {
    return file == nullptr;
}
