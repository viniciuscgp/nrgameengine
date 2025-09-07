#pragma once
#include "KeyCode.h"

enum class KeyState {
    PRESSED,
    RELEASED,
    HELD
};

class IInput {
public:
    virtual ~IInput() = default;

    virtual void update() = 0;
    virtual void endFrame() = 0;

    virtual bool isKeyPressed(KeyCode key) const = 0;
    virtual bool isKeyReleased(KeyCode key) const = 0;
    virtual bool isKeyHeld(KeyCode key) const = 0;

    virtual int getMouseX() const = 0;
    virtual int getMouseY() const = 0;
    virtual bool isMouseButtonPressed(int button) const = 0;

    virtual bool quitRequested() const = 0;
};
