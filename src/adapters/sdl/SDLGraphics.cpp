#include "SDLGraphics.h"
#include "SDLSurface.h"
#include <iostream>

SDLGraphics::SDLGraphics() : window(nullptr), renderer(nullptr) {}

SDLGraphics::~SDLGraphics() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

bool SDLGraphics::init(int width, int height, const std::string& title) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Erro SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Erro SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void SDLGraphics::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLGraphics::drawSurface(std::shared_ptr<ISurface> surface, int x, int y) {
    auto sdlSurface = std::dynamic_pointer_cast<SDLSurface>(surface);
    if (!sdlSurface) return;

    SDL_Rect dst { x, y, sdlSurface->getWidth(), sdlSurface->getHeight() };
    SDL_RenderCopy(renderer, sdlSurface->getTexture(), nullptr, &dst);
}

void SDLGraphics::drawRect(int x, int y, int w, int h,
                           int r, int g, int b, int a) {
    SDL_Rect rect { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void SDLGraphics::present() {
    SDL_RenderPresent(renderer);
}
