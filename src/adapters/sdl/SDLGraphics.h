#pragma once
#include "ports/IGraphics.h"
#include <SDL2/SDL.h>
#include <memory>

class SDLGraphics : public IGraphics {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    SDLGraphics();
    ~SDLGraphics() override;

    bool init(int width, int height, const std::string& title) override;
    void clear() override;
    void drawSurface(std::shared_ptr<ISurface> surface, int x, int y) override;

    // novo método
    void drawRect(int x, int y, int w, int h,
                  int r, int g, int b, int a) override;

    void present() override;

    SDL_Renderer* getRenderer() const { return renderer; }
};
