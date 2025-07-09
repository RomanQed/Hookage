//
// Created by Roman on 08.08.2023.
//

#include <windows.h>
#include <fcntl.h>
#include <stdexcept>
#include "winapi/WinConsoleFactory.h"
#include "base/FileInputStream.h"
#include "base/FileOutputStream.h"

using std::make_shared;
using std::lock_guard;
using std::runtime_error;

static BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlEvent) {
    return dwCtrlEvent == CTRL_C_EVENT;
}

shared_ptr<Console> WinConsoleFactory::create() {
    lock_guard<mutex> guard(lock);
    if (console && !console->isClosed()) {
        return console;
    }
    if (!AllocConsole()) {
        return {};
    }
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
    RemoveMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
    int inHandle = _open_osfhandle((INT_PTR) GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
    int outHandle = _open_osfhandle((INT_PTR) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    auto in = _fdopen(inHandle, "r");
    auto out = _fdopen(outHandle, "w");
    if (in == nullptr || out == nullptr) {
        _close(inHandle);
        _close(outHandle);
        throw runtime_error("Cannot open console i/o handlers");
    }
    auto temp = make_shared<WinConsole>();
    temp->input = make_shared<FileInputStream>(in);
    temp->output = make_shared<FileOutputStream>(out);
    temp->closed = false;
    console = temp;
    return temp;
}

void WinConsoleFactory::WinConsole::close() {
    lock_guard<mutex> guard(lock);
    if (this->closed) {
        return;
    }
    input->close();
    output->close();
    SetConsoleCtrlHandler(ConsoleCtrlHandler, FALSE);
    FreeConsole();
    this->closed = true;
}

InputStream &WinConsoleFactory::WinConsole::getInput() {
    return *input;
}

OutputStream &WinConsoleFactory::WinConsole::getOutput() {
    return *output;
}

bool WinConsoleFactory::WinConsole::isClosed() {
    return false;
}
