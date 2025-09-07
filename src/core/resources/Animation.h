#pragma once
#include <string>
#include <vector>

class Animation {
public:
    std::string name;                 // ex: "player_walk"
    std::vector<std::string> frames;  // lista de imagens por nome
    int speed = 0;                    // velocidade em ticks/frame
};
