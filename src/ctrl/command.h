#pragma once
#include "../env/vec3.h"

class Command {
public:
    Command();
    Command(float vt, float vn, float vw, float kick, float chip, bool dribble);
    Command (Vec3 vel, float kick, float chip, bool dribble);

    void print();
    void printerr();
//private:
    ///Que louco
    ///
    ///muito louco
    ///
    ///Eu tambem
    float vt_, vn_, vw_;
    float kick_ , chip_;
    bool dribble_;
};
