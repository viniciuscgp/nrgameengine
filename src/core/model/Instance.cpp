#include "Instance.h"
#include "ports/IGraphics.h"
#include <cmath>

void Instance::step()
{
    // aplica forças
    x += force_x;
    y += force_y;

    // aplica atrito
    int signalx = (force_x > 0) ? 1 : (force_x < 0 ? -1 : 0);
    int signaly = (force_y > 0) ? 1 : (force_y < 0 ? -1 : 0);

    float new_fx = std::abs(force_x) - friction;
    float new_fy = std::abs(force_y) - friction;

    force_x = (new_fx > 0 ? new_fx : 0) * signalx;
    force_y = (new_fy > 0 ? new_fy : 0) * signaly;

    // se valores ficarem muito pequenos, zera (evita drift infinito)
    if (std::abs(force_x) < 0.001f)
        force_x = 0.0f;
    if (std::abs(force_y) < 0.001f)
        force_y = 0.0f;
}

void Instance::draw(IGraphics* graphics)
{
    if (!graphics) return;

    // placeholder: desenha um quadrado branco 32x32 na posição
    graphics->drawRect((int)x, (int)y, 32, 32, 255, 255, 255, 255);
}
