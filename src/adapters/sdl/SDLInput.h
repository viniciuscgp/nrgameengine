#pragma once
#include "ports/IInput.h"
#include <SDL2/SDL.h>
#include <map>

class SDLInput : public IInput {
private:
    std::map<KeyCode, KeyState> keyStates;
    std::map<int, KeyCode> translationTable; // SDL → VK

    int mouseX;
    int mouseY;
    std::map<int, bool> mouseButtons;
    bool quit;

    void initTranslationTable();

public:
    SDLInput();
    ~SDLInput() override = default;

    void update() override;     // coleta eventos SDL
    void endFrame() override;   // normaliza estados no fim do frame

    bool isKeyPressed(KeyCode key) const override;
    bool isKeyReleased(KeyCode key) const override;
    bool isKeyHeld(KeyCode key) const override;
    bool isOnState(KeyCode key, KeyState state) const;

    int getMouseX() const override { return mouseX; }
    int getMouseY() const override { return mouseY; }
    bool isMouseButtonPressed(int button) const override;

    bool quitRequested() const override { return quit; }
};
