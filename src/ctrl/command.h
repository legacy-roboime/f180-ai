#pragma once
#include "../env/vec3.h"

//! Command class holds the output robots
//! may receive to perform actions.

class Command {
public:
    Command();
    Command(float vt, float vn, float vw, float kick, float chip, bool dribble);
    Command (Vec3 vel, float kick, float chip, bool dribble);

    void print();
    void printerr();

    float vt_, vn_, vw_;
    float kick_ , chip_;
    bool dribble_;
};
