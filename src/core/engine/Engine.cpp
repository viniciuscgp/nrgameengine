#include "Engine.h"
#include "core/model/Game.h"
#include "core/model/Scene.h" 
#include "ports/KeyCode.h"
#include "GameLoader.h"
#include <nlohmann/json.hpp>
#include <iostream>

Engine::Engine(std::unique_ptr<IGraphics> gfx,
               std::unique_ptr<IAudio> aud,
               std::unique_ptr<IInput> in,
               std::unique_ptr<ITimer> tim)
    : graphics(std::move(gfx)),
      audio(std::move(aud)),
      input(std::move(in)),
      timer(std::move(tim)),
      running(false) {}

Engine::~Engine() {}

bool Engine::init(int width, int height, const std::string &title,
                  const std::string &path) {
                    
    // carrega o JSON (padrão ./game.json ou o fornecido)
    game = GameLoader::load(path);
    if (!game) {
        std::cerr << "Erro ao carregar " << path << std::endl;
        return false;
    }
    std::cout << "Game carregado com sucesso: " << path << std::endl;

    // cria ScriptManager
    scriptManager = std::make_unique<ScriptManager>();
    scriptManager->registerAPI(game.get(), input.get(), audio.get());

    // dispara on_create da cena inicial
    auto scene = game->getCurrentScene();
    if (scene) {
        scene->triggerOnCreate(game.get(), scriptManager.get());
    }

    // aplica overrides 
    int finalWidth  = (game->width  > 0) ? game->width:width;
    int finalHeight = (game->height > 0) ? game->height:height;

    std::string finalTitle = !game->description.empty() ? game->description:title;

    // inicializa gráficos
    if (!graphics->init(finalWidth, finalHeight, finalTitle)) {
        std::cerr << "Erro ao iniciar gráficos!" << std::endl;
        return false;
    }

    running = true;
    return true;
}

void Engine::run() {
    while (running) {
        input->update();

        // sair com ESC ou se a janela for fechada
        if (input->isKeyHeld(KeyCode::VK_ESCAPE) || input->quitRequested()) {
            running = false;
        }

        graphics->clear();

        // --- Atualização do jogo ---
        if (game) {
            game->step(scriptManager.get()); 
        }

        input->endFrame();


        // --- Renderização ---
        if (game) {
            auto scene = game->getCurrentScene();
            if (scene) {
                scene->drawAll(graphics.get());
            }
        }

        graphics->present();

        // usa ITimer, não SDL direto
        timer->delay(16); // ~60 FPS
    }
}
