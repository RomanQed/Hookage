//
// Created by Roman on 15.08.2023.
//

#ifndef HOOKLOADER_HOOKEXCEPTION_H
#define HOOKLOADER_HOOKEXCEPTION_H

#include <exception>
#include <string_view>

using std::exception;
using std::wstring_view;

class HookException : public exception {
public:
    HookException(size_t error, const wstring_view &message) : errorCode(error), view(message) {}

    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override { return "Hook error"; }

    [[nodiscard]] size_t error() const { return errorCode; }

    [[nodiscard]] const wstring_view &message() const { return view; }

private:
    size_t errorCode;
    wstring_view view;
};


#endif //HOOKLOADER_HOOKEXCEPTION_H
