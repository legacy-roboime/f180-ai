#pragma once

#include "../env/vec3.h"
#include "command.h"

//TODO: refactor how calc works (currently void)
//REMINDER: maybe we add some different controls for
//specific agents, (i.e a specific control for the goalie) so this might change.

//! PID class is designed to aplly proportional, integral and derivative
//! controls in a certain command. Currently this class specificly applies
//! position control.

const float PL = 1.30f;
const float PW = 1.80f;

class PID{
public:
    PID() = default;
    PID(Command& cmd);

    void setCommandPtr(Command& cmd);
    void calcProportional(const Vec3 pose_now, const Vec3 pose_then);
private:
    Command* cmd_;
};
