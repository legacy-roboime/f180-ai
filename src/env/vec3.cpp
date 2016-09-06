#include "vec3.h"
#include <cmath>

float Vec3::magnitude(){
  return sqrt(x_*x_ + y_*y_);
}

float Vec3::dist(const Vec3 target){
  return sqrt((target.x_-x_)*(target.x_-x_) + (target.y_-y_)*(target.y_-y_));
}

float Vec3::dist2(const Vec3 target){
  return ((target.x_-x_)*(target.x_-x_) + (target.y_-y_)*(target.y_-y_));
}

Vec3 Vec3::normalize(){
  const Vec3 vec (x_,y_,w_);
  const float EPS = 1e-9;
  if(fabs(sqrt(vec.x_*vec.x_ + vec.y_*vec.y_))<EPS) return Vec3(0.0f, 0.0f ,w_);
  return vec*(1/(sqrt(vec.x_*vec.x_ + vec.y_*vec.y_)));
}

