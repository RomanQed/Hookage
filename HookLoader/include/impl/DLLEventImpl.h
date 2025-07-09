//
// Created by Roman on 24.08.2023.
//

#ifndef HOOKLOADER_DLLEVENTIMPL_H
#define HOOKLOADER_DLLEVENTIMPL_H


#include "events/DLLEvent.h"

class DLLEventImpl : public DLLEvent {
public:
    [[nodiscard]] HINSTANCE getInstance() const noexcept override;

    [[nodiscard]] DWORD getReason() const noexcept override;

    void setInstance(HINSTANCE value);

    void setReason(DWORD value);

private:
    HINSTANCE instance{};
    DWORD reason{};
};


#endif //HOOKLOADER_DLLEVENTIMPL_H
