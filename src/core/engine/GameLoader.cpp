#include "GameLoader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "core/resources/Image.h"
#include "core/resources/Animation.h"
#include "core/resources/Sound.h"
#include "core/resources/Script.h"
#include "core/model/Entity.h"
#include "core/model/Scene.h"
#include "core/model/Instance.h"

using json = nlohmann::json;

std::shared_ptr<Game> GameLoader::load(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Erro: não foi possível abrir " << path << std::endl;
        std::exit(1);
    }

    json j;
    try
    {
        file >> j;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro ao parsear JSON: " << e.what() << std::endl;
        std::exit(1);
    }

    // se existir "game", usa ele como raiz; senão usa o JSON direto
    auto root = j.contains("game") ? j["game"] : j;

    auto game = std::make_shared<Game>();

    // Metadados
    game->name = root.value("name", "SemNome");
    game->description = root.value("description", "NRGameEngine");
    game->version = root.value("version", "0.0");
    game->author = root.value("author", "Desconhecido");
    game->width = root.value("width", 800);
    game->height = root.value("height", 600);

    // Images
    if (root.contains("images"))
    {
        for (auto &img : root["images"])
        {
            auto image = std::make_shared<Image>();
            image->name = img.value("name", "");
            image->path = img.value("file_name", "");
            if (!image->name.empty())
            {
                game->images[image->name] = image;
                std::cout << "added image " << image->name << std::endl;
            }
        }
    }

    // Animations
    if (root.contains("animations"))
    {
        for (auto &anim : root["animations"])
        {
            auto animation = std::make_shared<Animation>();
            animation->name = anim.value("name", "");
            animation->frames = anim.value("frames", std::vector<std::string>{});
            animation->speed = anim.value("speed", 0);
            if (!animation->name.empty())
            {
                game->animations[animation->name] = animation;
                std::cout << "added animation " << animation->name << std::endl;
            }
        }
    }

    // Sounds
    if (root.contains("sounds"))
    {
        for (auto &snd : root["sounds"])
        {
            auto sound = std::make_shared<Sound>();
            sound->name = snd.value("name", "");
            sound->path = snd.value("file_name", "");
            if (!sound->name.empty())
            {
                game->sounds[sound->name] = sound;
                std::cout << "added sound " << sound->name << std::endl;
            }
        }
    }

    // Scripts
    if (root.contains("scripts"))
    {
        for (auto &scr : root["scripts"])
        {
            auto script = std::make_shared<Script>();
            script->name = scr.value("name", "");
            script->code = scr.value("code", "");
            if (!script->name.empty())
            {
                game->scripts[script->name] = script;
                std::cout << "added script " << script->name << std::endl;
            }
        }
    }

    // Entities
    if (root.contains("entities"))
    {
        for (auto &ent : root["entities"])
        {
            auto entity = std::make_shared<Entity>();
            entity->name = ent.value("name", "");
            entity->animation_name = ent.value("animation_name", "");

            // eventos → nomes de scripts
            entity->on_create = ent.value("on_create", "");
            entity->on_destroy = ent.value("on_destroy", "");
            entity->on_step = ent.value("on_step", "");
            entity->on_collision = ent.value("on_collision", "");
            entity->on_keypress = ent.value("on_keypress", "");
            entity->on_joystick = ent.value("on_joystick", "");

            // alarms
            if (ent.contains("alarms"))
            {
                for (auto &al : ent["alarms"])
                {
                    Alarm alarm;
                    alarm.name = al.value("name", "");
                    alarm.counter = al.value("counter", 0);
                    alarm.on_activate = al.value("on_activate", "");
                    entity->alarms.push_back(alarm);
                    std::cout << "added alarm " << alarm.name << std::endl;
                }
            }

            if (!entity->name.empty())
            {
                game->entities[entity->name] = entity;
                std::cout << "added entity " << entity->name << std::endl;
            }
        }
    }

    // Scenes
    if (root.contains("scenes"))
    {
        for (auto &scn : root["scenes"])
        {
            auto scene = std::make_shared<Scene>();
            scene->name = scn.value("name", "");

            if (scn.contains("instances"))
            {
                for (auto &inst : scn["instances"])
                {
                    auto instance = std::make_shared<Instance>();
                    instance->entity_name = inst.value("entity_name", "");
                    instance->x = inst.value("x", 0);
                    instance->y = inst.value("y", 0);
                    instance->depth = inst.value("depth", 0);
                    instance->force_x = inst.value("force_x", 0.0f);
                    instance->force_y = inst.value("force_y", 0.0f);
                    instance->friction = inst.value("friction", 0.0f);
                    scene->instances.push_back(instance);
                }
            }
            game->scenes.push_back(scene);
            std::cout << "added scenes " << scene->name << std::endl;
        }
    }

    // Cena inicial
    game->currentSceneIndex = root.value("start_scene", 0);

    return game;
}
