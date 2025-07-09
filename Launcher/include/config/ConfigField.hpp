//
// Created by Roman on 16.08.2023.
//

#ifndef HOOKLOADER_CONFIGFIELD_HPP
#define HOOKLOADER_CONFIGFIELD_HPP

#include <string>
#include <utility>

using std::string;

template<class T>
class ConfigField {
public:
    explicit ConfigField(const string &name);

    [[nodiscard]] const string &getName() const noexcept;

    virtual T fromString(const string &value) = 0;

    virtual string toString(const T &value) = 0;

private:
    string name;
};

template<class T>
ConfigField<T>::ConfigField(const string &name) {
    this->name = name;
}

template<class T>
const string &ConfigField<T>::getName() const noexcept {
    return name;
}


#endif //HOOKLOADER_CONFIGFIELD_HPP
