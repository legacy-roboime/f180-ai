#pragma once

#include "vec3.h"

#define PI 3.14159265358979323846

namespace util{
    float rad(const float deg) ;
    float deg(const float rad) ;
    float wrap(const float ang) ;
    float dist(const Vec3 pose1, const Vec3 pose2) ;
    float dist2(const Vec3 pose1, const Vec3 pose2) ;
    float aim(const Vec3 shooter, const Vec3 target) ; //TODO:names
    float mod(const Vec3 vec);
    Vec3 rec(const float r, const float theta);
    Vec3 normalize(const Vec3 vec) ;
}

