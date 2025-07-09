//
// Created by Roman on 07.08.2023.
//

#include "base/FileInputStream.h"

using std::lock_guard;

int FileInputStream::read() {
    lock_guard<mutex> guard(lock);
    checkFile();
    return fgetc(file);
}

string FileInputStream::readLine() {
    lock_guard<mutex> guard(lock);
    checkFile();
    string ret;
    int temp;
    while ((temp = fgetc(file)) != EOF && temp != '\n') {
        ret.push_back((char) temp);
    }
    return ret;
}

int FileInputStream::read(const char *format, va_list args) {
    lock_guard<mutex> guard(lock);
    checkFile();
    return vfscanf(file, format, args);
}

void FileInputStream::close() {
    FileStream::close();
}

bool FileInputStream::isClosed() {
    return FileStream::isClosed();
}
