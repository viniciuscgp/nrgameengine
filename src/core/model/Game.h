#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

// Forward declarations
class Image;
class Animation;
class Sound;
class Script;
class Entity;
class Scene;

class Game {
public:
    // --- Metadados ---
    std::string name;
    std::string description;
    std::string version;
    std::string author;

    // --- Configuração da janela ---
    int width = 800;
    int height = 600;

    // --- Recursos como mapas ---
    std::unordered_map<std::string, std::shared_ptr<Image>> images;
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations;
    std::unordered_map<std::string, std::shared_ptr<Sound>> sounds;
    std::unordered_map<std::string, std::shared_ptr<Script>> scripts;
    std::unordered_map<std::string, std::shared_ptr<Entity>> entities;  // <<< agora é mapa

    // --- Cenas ---
    std::vector<std::shared_ptr<Scene>> scenes;

    // --- Cena atual em execução ---
    int currentSceneIndex = -1;

    Game() = default;

    // Helpers para buscar recurso
    std::shared_ptr<Image> getImage(const std::string& name) const {
        auto it = images.find(name);
        return (it != images.end()) ? it->second : nullptr;
    }

    std::shared_ptr<Animation> getAnimation(const std::string& name) const {
        auto it = animations.find(name);
        return (it != animations.end()) ? it->second : nullptr;
    }

    std::shared_ptr<Sound> getSound(const std::string& name) const {
        auto it = sounds.find(name);
        return (it != sounds.end()) ? it->second : nullptr;
    }

    std::shared_ptr<Script> getScript(const std::string& name) const {
        auto it = scripts.find(name);
        return (it != scripts.end()) ? it->second : nullptr;
    }

    std::shared_ptr<Entity> getEntity(const std::string& name) const {
        auto it = entities.find(name);
        return (it != entities.end()) ? it->second : nullptr;
    }

    std::shared_ptr<Scene> getCurrentScene() const;
    void setCurrentScene(int index);
    void nextScene();
    void step(class ScriptManager* sm);
};
