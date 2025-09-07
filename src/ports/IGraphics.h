#pragma once
#include <string>
#include <memory>

class ISurface;

class IGraphics {
public:
    virtual ~IGraphics() = default;

    virtual bool init(int width, int height, const std::string& title) = 0;
    virtual void clear() = 0;
    virtual void drawSurface(std::shared_ptr<ISurface> surface, int x, int y) = 0;

    // novo: desenhar um retângulo preenchido
    virtual void drawRect(int x, int y, int w, int h,
                          int r, int g, int b, int a) = 0;

    virtual void present() = 0;
};
