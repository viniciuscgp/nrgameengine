#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Instance.h"
#include "ports/IGraphics.h"

class Game;
class ScriptManager;

class Scene {
public:
    std::string name;
    std::vector<std::shared_ptr<Instance>> instances;

    void stepAll(Game* game, ScriptManager* sm);
    void drawAll(IGraphics* graphics);

    // já existe
    void addInstance(std::shared_ptr<Instance> inst, Game* game, ScriptManager* sm);

    // novo: dispara on_create para todas as instâncias existentes
    void triggerOnCreate(Game* game, ScriptManager* sm);
};
