//
// Created by Roman on 16.08.2023.
//

#ifndef HOOKLOADER_CONFIG_HPP
#define HOOKLOADER_CONFIG_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>
#include "ConfigField.hpp"

using std::unordered_map;
using std::string;
using std::runtime_error;

#define SEPARATOR '='
#define COMMENT '#'

class Config {
public:
    explicit Config(const unordered_map<string, string> &init) : fields(init) {}

    Config() = default;

    [[nodiscard]] const unordered_map<string, string> &getFields() const noexcept {
        return this->fields;
    }

    [[nodiscard]] bool hasField(const string &name) const {
        return fields.find(name) != fields.end();
    }

    [[nodiscard]] const string &getField(const string &name) const {
        auto found = fields.find(name);
        if (found == fields.end()) {
            throw runtime_error("Required field not found");
        }
        return found->second;
    }

    template<class T>
    [[nodiscard]] T getField(ConfigField<T> &&field) const;

    template<class T>
    [[nodiscard]] T getField(ConfigField<T> &&field, const T &&def) const;

    template<class T>
    void setField(ConfigField<T> &&field, const T &&value);

private:
    unordered_map<string, string> fields;
};

template<class T>
T Config::getField(ConfigField<T> &&field) const {
    auto found = fields.find(field.getName());
    if (found == fields.end()) {
        throw runtime_error("Required field not found");
    }
    return field.fromString(found->second);
}

template<class T>
T Config::getField(ConfigField<T> &&field, const T &&def) const {
    auto found = fields.find(field.getName());
    if (found == fields.end()) {
        return def;
    }
    return field.fromString(found->second);
}

template<class T>
void Config::setField(ConfigField<T> &&field, const T &&value) {
    fields[field.getName()] = field.toString(value);
}

#endif //HOOKLOADER_CONFIG_HPP
