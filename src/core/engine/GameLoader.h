#pragma once
#include <memory>
#include <string>
#include "core/model/Game.h"

class GameLoader {
public:
    static std::shared_ptr<Game> load(const std::string& path);
};
