#pragma once
#include <string>

class ISurface {
public:
    virtual ~ISurface() = default;

    virtual bool loadFromFile(const std::string& path) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};
