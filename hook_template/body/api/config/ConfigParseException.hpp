//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_CONFIGPARSEEXCEPTION_HPP
#define HOOKLOADER_CONFIGPARSEEXCEPTION_HPP

#include <exception>
#include <string>

using std::exception;
using std::string;

class ConfigParseException : public exception {
public:
    explicit ConfigParseException(const string &badLine);

    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;

    [[nodiscard]] const string &getLine() const;

private:
    string badLine;
};

ConfigParseException::ConfigParseException(const string &badLine) {
    this->badLine = badLine;
}

const char *ConfigParseException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "Cannot read config due to bad line";
}

const string &ConfigParseException::getLine() const {
    return this->badLine;
}


#endif //HOOKLOADER_CONFIGPARSEEXCEPTION_HPP
