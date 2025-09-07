// src/ports/ITimer.h
#pragma once

class ITimer {
public:
    virtual ~ITimer() = default;

    virtual void delay(unsigned int ms) = 0;
    virtual unsigned int getTicks() const = 0; // opcional, tempo desde init
};
