#include "SDLSurface.h"
#include "SDLGraphics.h"
#include <iostream>

SDLSurface::SDLSurface(SDLGraphics* gfx)
    : texture(nullptr), width(0), height(0), graphics(gfx) {}

SDLSurface::~SDLSurface() {
    if (texture) SDL_DestroyTexture(texture);
}

bool SDLSurface::loadFromFile(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Erro IMG_Load: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(graphics->getRenderer(), surface);
    if (!texture) {
        std::cerr << "Erro SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
    return true;
}
