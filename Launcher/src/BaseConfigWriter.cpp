//
// Created by Roman on 27.08.2023.
//

#include "impl/BaseConfigWriter.h"
#include <fstream>
#include <string>

using std::ofstream;
using std::ios_base;
using std::string;
using std::endl;

void BaseConfigWriter::write(const char *name, const Config &config) {
    ofstream file(name, ios_base::out);
    const auto &data = config.getFields();
    for (const auto &entry: data) {
        file << entry.first << SEPARATOR << entry.second << endl;
    }
    file.close();
}
