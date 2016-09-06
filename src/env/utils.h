#pragma once

#include "vec3.h"

#define PI 3.14159265358979323846

///Utility functions
namespace util{
  ///Convert angle from degrees to radians
  float rad(const float ang) ;
  ///Convert angle from radians to degrees
  float deg(const float ang) ;
  ///Wrap angle to [-&pi;, &pi;]
  float wrap(const float ang) ;
  ///Return distance between pose1 and pose2
  float dist(const Vec3 pose1, const Vec3 pose2) ;
  ///Return distance^2 between pose1 and pose2
  float dist2(const Vec3 pose1, const Vec3 pose2) ;
  ///Return angle from source to target with x-axis
  float aim(const Vec3 source, const Vec3 target) ; //TODO:names
  ///Return vector modulus
  float mod(const Vec3 vec);
  ///Return the associated unitary vector
  Vec3 normalize(const Vec3 vec) ;
  ///Transform the vector (r,theta,phi) from polar coordinates to rectangular coordinates
  Vec3 rec(const float r, const float theta, const float phi);
  ///Transform the vector pol_vec from polar coordinates to rectangular coordinates
  Vec3 rec(const Vec3 pol_vec);
}

