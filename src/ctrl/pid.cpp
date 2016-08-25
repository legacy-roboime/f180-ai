#include "pid.h"
#include "../env/utils.h"
#include <cmath>

// TODO: test if wrapping before alters result (it shouldn't)

PID::PID(Command& cmd){
    cmd_ = &cmd; 
}

void PID::calcProportional(const Vec3 pose_now, const Vec3 pose_then) {
    cmd_->vt_ = PL * ((pose_then.x_ - pose_now.x_) * cos(pose_now.w_) + (pose_then.y_ - pose_now.y_) * sin(pose_now.w_));
    cmd_->vn_ = PL * ((pose_then.y_ - pose_now.y_) * cos(pose_now.w_) - (pose_then.x_ - pose_now.x_) * sin(pose_now.w_));
    cmd_->vw_ = PW * util::wrap(pose_then.w_ - pose_now.w_);
}

void PID::setCommandPtr(Command& cmd){
    cmd_ = &cmd;
}
