#pragma once

class CollisionBox {
public:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    bool intersects(const CollisionBox& other) const {
        return !(x + width < other.x ||
                 x > other.x + other.width ||
                 y + height < other.y ||
                 y > other.y + other.height);
    }
};
