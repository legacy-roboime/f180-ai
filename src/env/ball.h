#pragma once

#include "vec3.h"

struct Ball{
    Vec3 pose_,vel_;
    Ball (Vec3 pose , Vec3 vel):
        pose_(pose),
        vel_(vel) {};
};
