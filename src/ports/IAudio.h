#pragma once
#include <string>

class IAudio {
public:
    virtual ~IAudio() = default;

    virtual bool loadSound(const std::string& id, const std::string& path) = 0;
    virtual void playSound(const std::string& id) = 0;

    virtual bool loadMusic(const std::string& id, const std::string& path) = 0;
    virtual void playMusic(const std::string& id, int loops = -1) = 0;
    virtual void stopMusic() = 0;
};
