#include "Scene.h"
#include "Game.h"
#include "Entity.h"
#include "core/resources/Script.h"
#include "core/engine/ScriptManager.h"
#include <iostream>

void Scene::stepAll(Game* game, ScriptManager* sm) {
    for (auto& inst : instances) {
        if (!inst) continue;

        inst->step(); // física (forças/atrito)

        auto entity = game->getEntity(inst->entity_name);
        if (entity && !entity->on_step.empty()) {
            auto scr = game->getScript(entity->on_step);
            if (scr) {
                sm->runInstanceCode(inst.get(), scr->code);
            }
        }
    }
}

void Scene::drawAll(IGraphics* graphics) {
    for (auto& inst : instances) {
        if (inst) {
            inst->draw(graphics);
        }
    }
}

void Scene::addInstance(std::shared_ptr<Instance> inst, Game* game, ScriptManager* sm) {
    instances.push_back(inst);

    auto entity = game->getEntity(inst->entity_name);
    if (entity && !entity->on_create.empty()) {
        auto scr = game->getScript(entity->on_create);
        if (scr) {
            sm->runInstanceCode(inst.get(), scr->code);
        }
    }
}

// novo
void Scene::triggerOnCreate(Game* game, ScriptManager* sm) {
    for (auto& inst : instances) {
        auto entity = game->getEntity(inst->entity_name);
        if (entity && !entity->on_create.empty()) {
            auto scr = game->getScript(entity->on_create);
            if (scr) {
                sm->runInstanceCode(inst.get(), scr->code);
            }
        }
    }
}
