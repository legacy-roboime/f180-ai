#pragma once

#include "vec3.h"

#define PI 3.14159265358979323846
const float EPS = 1e-9;

///Utility functions
namespace util{
  ///Clamps value between min and max
  float clamp(float value, const float min, const float max);
  ///Converts angle from degrees to radians
  float rad(const float ang) ;
  ///Converts angle from radians to degrees
  float deg(const float ang) ;
  ///Wraps angle to [-&pi;, &pi;]
  float wrap(const float ang) ;
  ///Returns distance between pose1 and pose2
  float dist(const Vec3 pose1, const Vec3 pose2) ;
  ///Returns square of distance between pose1 and pose2
  float dist2(const Vec3 pose1, const Vec3 pose2) ;
  ///Returns angle from source to target with x-axis
  float aim(const Vec3 source, const Vec3 target) ; //TODO:names
  ///Returns vector 2D norm
  float norm2(const Vec3 vec) ;
  ///Returns the equivalent unitary vector
  Vec3 normalize(const Vec3 vec) ;
  ///Transforms the vector (r,theta,phi) from polar coordinates to rectangular coordinates
  Vec3 rec(const float r, const float theta, const float phi) ;
  ///Transforms the vector pol_vec from polar coordinates to rectangular coordinates
  Vec3 rec(const Vec3 pol_vec) ;
}

