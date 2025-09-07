#include "SDLAudio.h"
#include <iostream>

SDLAudio::SDLAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erro Mix_OpenAudio: " << Mix_GetError() << std::endl;
    }
}

SDLAudio::~SDLAudio() {
    for (auto& [id, chunk] : sounds) {
        Mix_FreeChunk(chunk);
    }
    for (auto& [id, music] : musics) {
        Mix_FreeMusic(music);
    }
    Mix_CloseAudio();
}

bool SDLAudio::loadSound(const std::string& id, const std::string& path) {
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        std::cerr << "Erro Mix_LoadWAV (" << path << "): " << Mix_GetError() << std::endl;
        return false;
    }
    sounds[id] = sound;
    return true;
}

void SDLAudio::playSound(const std::string& id) {
    auto it = sounds.find(id);
    if (it != sounds.end()) {
        Mix_PlayChannel(-1, it->second, 0);
    }
}

bool SDLAudio::loadMusic(const std::string& id, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Erro Mix_LoadMUS (" << path << "): " << Mix_GetError() << std::endl;
        return false;
    }
    musics[id] = music;
    return true;
}

void SDLAudio::playMusic(const std::string& id, int loops) {
    auto it = musics.find(id);
    if (it != musics.end()) {
        if (Mix_PlayMusic(it->second, loops) == -1) {
            std::cerr << "Erro Mix_PlayMusic: " << Mix_GetError() << std::endl;
        }
    }
}

void SDLAudio::stopMusic() {
    Mix_HaltMusic();
}
