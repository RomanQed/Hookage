//
// Created by Roman on 07.08.2023.
//

#include <stdexcept>
#include "base/FileOutputStream.h"

using std::overflow_error;
using std::lock_guard;

void FileOutputStream::write(int value) {
    lock_guard<mutex> guard(lock);
    checkFile();
    if (putc(value, file) == EOF || fflush(file) == EOF) {
        throw overflow_error("Cannot write byte to file");
    }
}

void FileOutputStream::write(const char *value, size_t length) {
    lock_guard<mutex> guard(lock);
    checkFile();
    for (size_t i = 0; i < length; ++i) {
        if (putc(value[i], file) == EOF) {
            throw overflow_error("Cannot write string to file");
        }
    }
    if (fflush(file) == EOF) {
        throw overflow_error("Cannot write string to file");
    }
}

void FileOutputStream::write(const string_view &value) {
    this->write(value.data(), value.length());
}

void FileOutputStream::write(const string &value) {
    lock_guard<mutex> guard(lock);
    checkFile();
    if (fputs(value.c_str(), file) == EOF) {
        throw overflow_error("Cannot write string to file");
    }
    if (fflush(file) == EOF) {
        throw overflow_error("Cannot write string to file");
    }
}

int FileOutputStream::write(const char *format, va_list args) {
    lock_guard<mutex> guard(lock);
    checkFile();
    int ret = vfprintf(file, format, args);
    if (fflush(file) == EOF) {
        throw overflow_error("Cannot write formatted string to file");
    }
    return ret;
}

void FileOutputStream::close() {
    FileStream::close();
}

bool FileOutputStream::isClosed() {
    return FileStream::isClosed();
}
