#include "utils.h"
#include <cmath>
#include <algorithm>

float util::clamp(float value, const float min, const float max) {
  return std::min(max, std::max(value,min));
}

float util::rad(const float ang) {
  return (PI*ang/180.0);
}

float util::deg(const float ang) {
  return (180.0*ang/PI);
}

float util::wrap(const float ang) {
  return (fmod(ang + 5 * PI, 2 * PI) - PI);
}

float util::dist(const Vec3 pose1, const Vec3 pose2) {
  const float dx_2 = (pose1.x-pose2.x)*(pose1.x-pose2.x);
  const float dy_2 = (pose1.y-pose2.y)*(pose1.y-pose2.y);
  return sqrt(dx_2+dy_2);
}
float util::dist2(const Vec3 pose1, const Vec3 pose2) {
  const float dx_2 = (pose1.x-pose2.x)*(pose1.x-pose2.x);
  const float dy_2 = (pose1.y-pose2.y)*(pose1.y-pose2.y);
  return (dx_2+dy_2);
}

float util::norm2(const Vec3 vec) {
  return sqrt(vec.x*vec.x + vec.y*vec.y);
}

float util::aim(const Vec3 source, const Vec3 target) {
  const float x = target.x - source.x;
  const float y = target.y - source.y;
  return atan2(y,x);
}

Vec3 util::normalize(const Vec3 vec) {
  if(fabs(norm2(vec))<EPS) return Vec3();
  return vec*(1/norm2(vec));
}

Vec3 util::rec(const float r, const float theta, const float phi) {
  return Vec3(r*cos(theta),r*sin(theta),phi);
}

Vec3 util::rec(const Vec3 pol_vec) {
  const float r = pol_vec.x, theta = pol_vec.y, phi=pol_vec.w;
  return Vec3(r*cos(theta),r*sin(theta),phi);
}

