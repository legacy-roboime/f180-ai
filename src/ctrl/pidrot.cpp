#include "pidrot.h"
#include "../env/utils.h"
#include <cmath>
#include <iostream>

using namespace std;

// TODO: test if wrapping before alters result (it shouldn't)

PIDRot::PIDRot(Command& cmd){
  cmd_ = &cmd;
}


//! Position controlling method. Set speeds so vertical and horizontal speeds are proportional
//! to the differences between current and desired points along each axis. Since the current
//! protocol requires normal and tangent speeds to be the output, we must apply a transformation
//! on these differencesfrom the cartesian field axis (xy) to the robots' tangent and normal axis'.
void PIDRot::calcProportional(const Vec3 pose_now, const Vec3 center, const float radius, const float angle) {
  float theta = util::wrap(center.aim(pose_now));
  float dw = util::wrap(angle - theta);
  float dr = radius - pose_now.dist(center);
  float vt = (radius-dr)*PT*dw;
  float vr = PR*dr;
  float vx = vr*cos(theta) - vt*sin(theta);
  float vy = vr*sin(theta) + vt*cos(theta);
  float alpha = util::wrap(pose_now.w);
  float vt_ = vx*cos(alpha)+vy*sin(alpha);
  float vn_ = -vx*sin(alpha)+vy*cos(alpha);
  float vw_ = PW*util::wrap(pose_now.aim(center)-pose_now.w);
  //vt_ = vn_ = 0;
  //vw_=0;
  cmd_-> vt_ = vt_;
  cmd_-> vn_ = vn_;
  cmd_-> vw_ = vw_;
  //cerr << vr << ' ' << vt << ' ' << vw_ << endl;
}

void PIDRot::setCommandPtr(Command& cmd){
  cmd_ = &cmd;
}
