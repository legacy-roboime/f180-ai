#include "utils.h"
#include <cmath>

const float EPS = 1e-9;

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
  const float dx_2 = (pose1.x_-pose2.x_)*(pose1.x_-pose2.x_);
  const float dy_2 = (pose1.y_-pose2.y_)*(pose1.y_-pose2.y_);
  return sqrt(dx_2+dy_2);
}
float util::dist2(const Vec3 pose1, const Vec3 pose2) {
  const float dx_2 = (pose1.x_-pose2.x_)*(pose1.x_-pose2.x_);
  const float dy_2 = (pose1.y_-pose2.y_)*(pose1.y_-pose2.y_);
  return (dx_2+dy_2);
}


float util::mod(const Vec3 vec){
  return sqrt(vec.x_*vec.x_ + vec.y_*vec.y_);
}

float util::aim(const Vec3 source, const Vec3 target){
  const float x = target.x_ - source.x_;
  const float y = target.y_ - source.y_;
  return atan2(y,x);
}

Vec3 util::normalize(const Vec3 vec){
  if(fabs(mod(vec))<EPS) return vec;
  return vec*(1/mod(vec));
}

Vec3 util::rec(const float r, const float theta, const float phi) {
  return Vec3(r*cos(theta),r*sin(theta),phi);
}

Vec3 util::rec(const Vec3 pol_vec) {
  const float r = pol_vec.x_, theta = pol_vec.y_, phi=pol_vec.z_;
  return Vec3(r*cos(theta),r*sin(theta),phi);
}
