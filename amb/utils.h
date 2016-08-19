#pragma once

#include <cmath>

#include "pose.h"

#define PI 3.14159265358979323846

// TODO: move these constants to control dir when rdy
const float PW = 1.80f;
const float PL = 1.50f;

namespace util{
    float rad(const float deg) ; 
    float deg(const float rad) ; 
    float wrap(const float ang) ;
    float dist(const Pose p_1, const Pose p_2);
}

