#include "vec3.h"
#include <assert.h>
#include <cmath>
float Vec3::length() const {
  return sqrt(x_*x_ + y_*y_);
}

float Vec3::dist(const Vec3 target) const {
  return sqrt((target.x_-x_)*(target.x_-x_) + (target.y_-y_)*(target.y_-y_));
}

float Vec3::dist2(const Vec3 target) const {
  return ((target.x_-x_)*(target.x_-x_) + (target.y_-y_)*(target.y_-y_));
}

Vec3 Vec3::normalized() const {
  const Vec3 vec (x_,y_,w_);
  const float EPS = 1e-9;
  if(fabs(sqrt(vec.x_*vec.x_ + vec.y_*vec.y_))<EPS) return Vec3(0.0f, 0.0f ,w_);
  return vec*(1/(sqrt(vec.x_*vec.x_ + vec.y_*vec.y_)));
}

//Follows the formula cos(angle) = A*B/|A||B|
float Vec3::ang(const Vec3 vec2) const {
  const Vec3 vec1 (x_,y_,w_);
  assert(vec1.length()*vec2.length() != 0);
  return acos(vec1*vec2/(vec1.length()*vec2.length()));
}


