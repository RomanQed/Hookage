//
// Created by Roman on 24.08.2023.
//

#include "util/LongField.h"

using std::stoll;
using std::to_string;

ssize_t LongField::fromString(const string &value) {
    return stoll(value);
}

string LongField::toString(const ssize_t &&value) {
    return to_string(value);
}
