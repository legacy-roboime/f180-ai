#include "pid.h"
#include "../env/utils.h"
#include <cmath>

// TODO: test if wrapping before alters result (it shouldn't)

PID::PID(Command& cmd){
    cmd_ = &cmd;
}


//! Position controlling method. Set speeds so vertical and horizontal speeds are proportional
//! to the differences between current and desired points along each axis. Since the current
//! protocol requires normal and tangent speeds to be the output, we must apply a transformation
//! on these differencesfrom the cartesian field axis (xy) to the robots' tangent and normal axis'.
void PID::calcProportional(const Vec3 pose_now, const Vec3 pose_then) {
    cmd_->vt_ = PL * ((pose_then.x_ - pose_now.x_) * cos(pose_now.w_) + (pose_then.y_ - pose_now.y_) * sin(pose_now.w_));
    cmd_->vn_ = PL * ((pose_then.y_ - pose_now.y_) * cos(pose_now.w_) - (pose_then.x_ - pose_now.x_) * sin(pose_now.w_));
    cmd_->vw_ = PW * util::wrap(pose_then.w_ - pose_now.w_);
}

void PID::setCommandPtr(Command& cmd){
    cmd_ = &cmd;
}
