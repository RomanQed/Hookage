//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_CONSOLEFACTORY_H
#define HOOKLOADER_CONSOLEFACTORY_H

#include <memory>
#include "Console.h"

using std::shared_ptr;

class ConsoleFactory {
public:
    [[nodiscard]] virtual shared_ptr<Console> create() = 0;
};

#endif //HOOKLOADER_CONSOLEFACTORY_H
