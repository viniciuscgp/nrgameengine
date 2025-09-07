#pragma once

class Alarm {
public:
    int time = 0;
    bool active = false;

    void set(int t) { time = t; active = true; }
    void update() {
        if (active && time > 0) {
            --time;
            if (time == 0) active = false;
        }
    }
    bool finished() const { return !active; }
};
