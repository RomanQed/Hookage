//
// Created by Roman on 24.08.2023.
//

#include "util/DoubleField.h"

using std::stod;
using std::to_string;

double DoubleField::fromString(const string &value) {
    return stod(value);
}

string DoubleField::toString(const double &&value) {
    return to_string(value);
}
