#pragma once
#include "ports/IAudio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class SDLAudio : public IAudio {
private:
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*> musics;

public:
    SDLAudio();
    ~SDLAudio() override;

    bool loadSound(const std::string& id, const std::string& path) override;
    void playSound(const std::string& id) override;

    bool loadMusic(const std::string& id, const std::string& path) override;
    void playMusic(const std::string& id, int loops = -1) override;
    void stopMusic() override;
};
