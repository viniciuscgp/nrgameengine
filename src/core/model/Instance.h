#pragma once
#include <string>

class IGraphics;

class Instance {
public:
    std::string entity_name; 

    // Posição no mundo
    float x = 0.0f;
    float y = 0.0f;
    int depth = 0;

    // Forças aplicadas
    float force_x = 0.0f;
    float force_y = 0.0f;

    // Atrito (0 = sem atrito, 1 = para instantaneamente)
    float friction = 0.0f;

    // Atualiza a posição e aplica atrito
    void step();

    // Desenha a instância
    void draw(IGraphics* graphics);    
};
