//
// Created by Roman on 24.08.2023.
//

#include "impl/BaseConfigReader.h"
#include "config/ConfigParseException.hpp"
#include <fstream>
#include <string>
#include <functional>
#include <cctype>

using std::ifstream;
using std::ios_base;
using std::string;
using std::pair;
using std::find_if;
using std::not1;
using std::ptr_fun;

// trim from start (in place)
static inline void ltrim(std::string &value) {
    value.erase(value.begin(), find_if(value.begin(), value.end(), not1(ptr_fun<int, int>(isspace))));
}

// trim from end (in place)
static inline void rtrim(string &value) {
    value.erase(find_if(value.rbegin(), value.rend(), not1(ptr_fun<int, int>(isspace))).base(), value.end());
}

// trim from both ends (in place)
static inline void trim(string &value) {
    rtrim(value);
    ltrim(value);
}

static pair<string, string> parse(const string &line) {
    // Split line by separator
    auto position = line.find(SEPARATOR);
    if (position == string::npos) {
        throw ConfigParseException(line);
    }
    auto key = line.substr(0, position);
    auto value = line.substr(position + 1, line.size() - position);
    trim(key);
    trim(value);
    return {key, value};
}

Config BaseConfigReader::read(const char *name) {
    ifstream file(name, ios_base::in);
    unordered_map<string, string> ret;
    string line;
    while (getline(file, line)) {
        trim(line);
        // Skip empty and comment lines
        if (line.empty() || line.at(0) == COMMENT) {
            continue;
        }
        auto entry = parse(line);
        ret[entry.first] = entry.second;
    }
    file.close();
    return Config(ret);
}
