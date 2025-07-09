//
// Created by Roman on 07.08.2023.
//

#ifndef HOOKLOADER_CLOSABLE_H
#define HOOKLOADER_CLOSABLE_H

class Closable {
public:
    virtual ~Closable() = default;

    virtual bool isClosed() = 0;

    virtual void close() = 0;
};

#endif //HOOKLOADER_CLOSABLE_H
