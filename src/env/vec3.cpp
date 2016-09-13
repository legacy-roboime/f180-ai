#include "vec3.h"
#include <assert.h>
#include <cmath>
float Vec3::length() const {
  return sqrt(x*x + y*y);
}

float Vec3::dist(const Vec3 target) const {
  return sqrt((target.x-x)*(target.x-x) + (target.y-y)*(target.y-y));
}

float Vec3::dist2(const Vec3 target) const {
  return ((target.x-x)*(target.x-x) + (target.y-y)*(target.y-y));
}

Vec3 Vec3::normalized() const {
  const Vec3 vec (x,y,w);
  const float EPS = 1e-9;
  if(fabs(sqrt(vec.x*vec.x + vec.y*vec.y))<EPS) return Vec3(0.0f, 0.0f ,w);
  return vec*(1/(sqrt(vec.x*vec.x + vec.y*vec.y)));
}

// Follows the equation cos(angle) = A*B/|A||B|
float Vec3::ang(const Vec3 vec2) const {
  const Vec3 vec1 (x,y,w);
  assert(vec1.length()*vec2.length() != 0);
  return acos(vec1*vec2/(vec1.length()*vec2.length()));
}

Vec3 Vec3::displaced(const float angle) const {
  const float radius = this->length();
  const float theta = atan2(y,x);
  return Vec3(radius*cos(angle+theta), radius*sin(angle+theta), w);
}

