//
// Created by Roman on 16.08.2023.
//

#ifndef HOOKLOADER_DLLEVENT_H
#define HOOKLOADER_DLLEVENT_H

#include <windows.h>

class DLLEvent {
public:
    [[nodiscard]] virtual HINSTANCE getInstance() const noexcept = 0;

    [[nodiscard]] virtual DWORD getReason() const noexcept = 0;
};


#endif //HOOKLOADER_DLLEVENT_H
