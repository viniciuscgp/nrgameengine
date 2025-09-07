#pragma once
#include "ports/ISurface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDLGraphics;

class SDLSurface : public ISurface {
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDLGraphics* graphics;

public:
    SDLSurface(SDLGraphics* gfx);
    ~SDLSurface() override;

    bool loadFromFile(const std::string& path) override;
    int getWidth() const override { return width; }
    int getHeight() const override { return height; }

    SDL_Texture* getTexture() const { return texture; }
};
