#pragma once
#include <memory>
#include <string>

// Ports
#include "ports/IGraphics.h"
#include "ports/IAudio.h"
#include "ports/IInput.h"
#include "ports/ITimer.h"
#include "ScriptManager.h"   // <<< novo

class Game;

class Engine {
private:
    std::unique_ptr<IGraphics> graphics;
    std::unique_ptr<IAudio> audio;
    std::unique_ptr<IInput> input;
    std::unique_ptr<ITimer> timer;

    std::shared_ptr<Game> game;     
    std::unique_ptr<ScriptManager> scriptManager; // <<< novo

    bool running;

public:
    Engine(std::unique_ptr<IGraphics> gfx,
           std::unique_ptr<IAudio> aud,
           std::unique_ptr<IInput> in,
           std::unique_ptr<ITimer> tim);

    ~Engine();

    bool init(int width, int height, const std::string& title,
              const std::string& path = "./game.json");

    void run();
};
