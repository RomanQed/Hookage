#include <iostream>
#include "impl/BaseConfigReader.h"
#include "Define.h"
#include "Util.h"
#include "impl/LongField.h"
#include "impl/BaseConfigWriter.h"

using std::cout;
using std::endl;
using std::exception;

int main(int argc, char **argv) {
    cout << "[INFO] Hello from Hookage Injector (simple thread-based injection)" << endl;
    // Check for argument correctness
    if (argc != 2) {
        cout << "[ERROR] Bad arguments" << endl;
        return 1;
    }
    try {
        // Get full path for current directory
        auto path = getCurrentDirectory();
        // Read config
        auto config = BaseConfigReader().read((path + '\\' + CONFIG).c_str());
        // Start process
        auto data = runProcess(argv[1], DETACHED_PROCESS | CREATE_SUSPENDED);
        // Write data to config
        config.setField(LongField(THREAD_ID), (long long) data.dwThreadId);
        BaseConfigWriter().write(CONFIG, config);
        // Inject dependency dll
        inject(data.dwProcessId, (path + '\\' + LIB_DLL).c_str());
        cout << "[INFO] EasyHook dll injected" << endl;
        // Inject loader dll
        inject(data.dwProcessId, (path + '\\' + LOADER_DLL).c_str());
        cout << "[INFO] HookLoader dll injected" << endl;
        cout << "[INFO] Exiting" << endl;
    } catch (const exception &e) {
        cout << "[ERROR] Something went wrong: " << e.what() << endl;
        return 1;
    }
    return 0;
}
