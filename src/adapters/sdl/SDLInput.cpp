#include "SDLInput.h"

SDLInput::SDLInput() : mouseX(0), mouseY(0), quit(false) {
    initTranslationTable();
}

void SDLInput::initTranslationTable() {
    // Letras A–Z
    translationTable[SDLK_a] = KeyCode::VK_A;
    translationTable[SDLK_b] = KeyCode::VK_B;
    translationTable[SDLK_c] = KeyCode::VK_C;
    translationTable[SDLK_d] = KeyCode::VK_D;
    translationTable[SDLK_e] = KeyCode::VK_E;
    translationTable[SDLK_f] = KeyCode::VK_F;
    translationTable[SDLK_g] = KeyCode::VK_G;
    translationTable[SDLK_h] = KeyCode::VK_H;
    translationTable[SDLK_i] = KeyCode::VK_I;
    translationTable[SDLK_j] = KeyCode::VK_J;
    translationTable[SDLK_k] = KeyCode::VK_K;
    translationTable[SDLK_l] = KeyCode::VK_L;
    translationTable[SDLK_m] = KeyCode::VK_M;
    translationTable[SDLK_n] = KeyCode::VK_N;
    translationTable[SDLK_o] = KeyCode::VK_O;
    translationTable[SDLK_p] = KeyCode::VK_P;
    translationTable[SDLK_q] = KeyCode::VK_Q;
    translationTable[SDLK_r] = KeyCode::VK_R;
    translationTable[SDLK_s] = KeyCode::VK_S;
    translationTable[SDLK_t] = KeyCode::VK_T;
    translationTable[SDLK_u] = KeyCode::VK_U;
    translationTable[SDLK_v] = KeyCode::VK_V;
    translationTable[SDLK_w] = KeyCode::VK_W;
    translationTable[SDLK_x] = KeyCode::VK_X;
    translationTable[SDLK_y] = KeyCode::VK_Y;
    translationTable[SDLK_z] = KeyCode::VK_Z;

    // Números 0–9
    translationTable[SDLK_0] = KeyCode::VK_0;
    translationTable[SDLK_1] = KeyCode::VK_1;
    translationTable[SDLK_2] = KeyCode::VK_2;
    translationTable[SDLK_3] = KeyCode::VK_3;
    translationTable[SDLK_4] = KeyCode::VK_4;
    translationTable[SDLK_5] = KeyCode::VK_5;
    translationTable[SDLK_6] = KeyCode::VK_6;
    translationTable[SDLK_7] = KeyCode::VK_7;
    translationTable[SDLK_8] = KeyCode::VK_8;
    translationTable[SDLK_9] = KeyCode::VK_9;

    // Teclas especiais
    translationTable[SDLK_ESCAPE] = KeyCode::VK_ESCAPE;
    translationTable[SDLK_SPACE]  = KeyCode::VK_SPACE;
    translationTable[SDLK_RETURN] = KeyCode::VK_RETURN;
    translationTable[SDLK_TAB]    = KeyCode::VK_TAB;
    translationTable[SDLK_LSHIFT] = KeyCode::VK_SHIFT;
    translationTable[SDLK_RSHIFT] = KeyCode::VK_SHIFT;
    translationTable[SDLK_LCTRL]  = KeyCode::VK_CTRL;
    translationTable[SDLK_RCTRL]  = KeyCode::VK_CTRL;
    translationTable[SDLK_LALT]   = KeyCode::VK_ALT;
    translationTable[SDLK_RALT]   = KeyCode::VK_ALT;

    // Setas
    translationTable[SDLK_LEFT]  = KeyCode::VK_LEFT;
    translationTable[SDLK_RIGHT] = KeyCode::VK_RIGHT;
    translationTable[SDLK_UP]    = KeyCode::VK_UP;
    translationTable[SDLK_DOWN]  = KeyCode::VK_DOWN;
}

void SDLInput::update() {
    quit = false;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
            KeyCode code = translationTable.count(e.key.keysym.sym)
                ? translationTable[e.key.keysym.sym]
                : KeyCode::VK_UNKNOWN;
            keyStates[code] = KeyState::PRESSED;
        }
        else if (e.type == SDL_KEYUP) {
            KeyCode code = translationTable.count(e.key.keysym.sym)
                ? translationTable[e.key.keysym.sym]
                : KeyCode::VK_UNKNOWN;
            keyStates[code] = KeyState::RELEASED;
        }
        else if (e.type == SDL_MOUSEMOTION) {
            mouseX = e.motion.x;
            mouseY = e.motion.y;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            mouseButtons[e.button.button] = true;
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
            mouseButtons[e.button.button] = false;
        }
    }
}

void SDLInput::endFrame() {
    for (auto it = keyStates.begin(); it != keyStates.end();) {
        if (it->second == KeyState::PRESSED) {
            it->second = KeyState::HELD;
            ++it;
        }
        else if (it->second == KeyState::RELEASED) {
            it = keyStates.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool SDLInput::isKeyPressed(KeyCode key) const {
    auto it = keyStates.find(key);
    return (it != keyStates.end() && it->second == KeyState::PRESSED);
}

bool SDLInput::isKeyReleased(KeyCode key) const {
    auto it = keyStates.find(key);
    return (it != keyStates.end() && it->second == KeyState::RELEASED);
}

bool SDLInput::isKeyHeld(KeyCode key) const {
    auto it = keyStates.find(key);
    return (it != keyStates.end() && it->second == KeyState::HELD);
}

bool SDLInput::isMouseButtonPressed(int button) const {
    auto it = mouseButtons.find(button);
    return (it != mouseButtons.end() && it->second);
}
