#pragma once

// Conjunto de códigos de tecla da engine (independentes de backend)
enum class KeyCode:int {
    VK_UNKNOWN = 0,

    // Letras A–Z
    VK_A, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G,
    VK_H, VK_I, VK_J, VK_K, VK_L, VK_M, VK_N,
    VK_O, VK_P, VK_Q, VK_R, VK_S, VK_T, VK_U,
    VK_V, VK_W, VK_X, VK_Y, VK_Z,

    // Números 0–9
    VK_0, VK_1, VK_2, VK_3, VK_4,
    VK_5, VK_6, VK_7, VK_8, VK_9,

    // Teclas de controle
    VK_ESCAPE,
    VK_SPACE,
    VK_RETURN,
    VK_TAB,
    VK_SHIFT,
    VK_CTRL,
    VK_ALT,

    // Setas
    VK_LEFT,
    VK_RIGHT,
    VK_UP,
    VK_DOWN
};
