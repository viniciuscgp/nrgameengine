#include "Game.h"
#include "Scene.h"

std::shared_ptr<Scene> Game::getCurrentScene() const {
    if (currentSceneIndex >= 0 && currentSceneIndex < (int)scenes.size()) {
        return scenes[currentSceneIndex];
    }
    return nullptr;
}

void Game::setCurrentScene(int index) {
    if (index >= 0 && index < (int)scenes.size()) {
        currentSceneIndex = index;
    }
}

void Game::nextScene() {
    if (!scenes.empty()) {
        currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
    }
}

void Game::step(class ScriptManager* sm) {
    auto scene = getCurrentScene();
    if (scene) {
        scene->stepAll(this, sm);
    }
}

