//
// Created by Roman on 08.08.2023.
//

#ifndef HOOKLOADER_WINCONSOLEFACTORY_H
#define HOOKLOADER_WINCONSOLEFACTORY_H

#include <mutex>
#include "export/console/ConsoleFactory.h"
#include "base/BaseConsole.h"

using std::mutex;
using std::weak_ptr;

class WinConsoleFactory : public ConsoleFactory {
public:
    shared_ptr<Console> create() override;

private:
    mutex lock;
    shared_ptr<Console> console;

    class WinConsole;
};

class WinConsoleFactory::WinConsole : public BaseConsole {
public:
    void close() override;

    InputStream &getInput() override;

    OutputStream &getOutput() override;

    bool isClosed() override;

private:
    mutex lock;
    bool closed;
    shared_ptr<InputStream> input;
    shared_ptr<OutputStream> output;

    friend class WinConsoleFactory;
};


#endif //HOOKLOADER_WINCONSOLEFACTORY_H
