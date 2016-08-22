#pragma once

#include "../env/vec3.h"
#include "command.h"

//TODO: refactor how calc works (currently void)
//REMINDER: maybe we add some different controls, so this might change.


class PID{
public:
    PID() = default;
    PID(Command& cmd);
    void calcProportional(const Vec3 pose_now, const Vec3 pose_then);
private:
    const float PL = 1.50f; //TODO: friendly names, maybe?
    const float PW = 1.80f;
    Command* cmd_;
};
