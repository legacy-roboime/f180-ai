#pragma once

#include "../env/vec3.h"
#include "command.h"

//TODO: refactor how calc works (currently void)
//REMINDER: maybe we add some different controls for
//specific agents, (i.e a specific control for the goalie) so this might change.

//! PIDRot class is designed to aplly proportional, integral and derivative
//! controls in a certain command. Currently this class specificly applies
//! position control.


class PIDRot{
  public:
    const float PW = 1.00f;
    const float PR = 1.00f;
    const float PT = 1.00f;
    PIDRot() = default;
    PIDRot(Command& cmd);

    void setCommandPtr(Command& cmd);
    void calcProportional(const Vec3 pose_now, const Vec3 center, const float radius, const float angle);
  private:
    Command* cmd_;
};
