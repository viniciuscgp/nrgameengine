#pragma once
#include "ports/ITimer.h"
#include <SDL2/SDL.h>

class SDLTimer : public ITimer {
public:
    SDLTimer() = default;
    ~SDLTimer() override = default;

    void delay(unsigned int ms) override {
        SDL_Delay(ms);
    }

    unsigned int getTicks() const override {
        return SDL_GetTicks();
    }
};
