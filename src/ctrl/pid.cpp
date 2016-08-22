#include "pid.h"
#include "../env/utils.h"
#include <cmath>

using namespace util;

// TODO: test if wrapping before alters result (it shouldn't)

PID::PID(Command& cmd){
    cmd_ = &cmd; 
}

void PID::calcProportional(const Vec3 pose_now, const Vec3 pose_then) {
    const float delta_w = wrap(pose_then.w_ - pose_now.w_); // 4 more bytes won't hurt anyone...
    cmd_->vt_ = PL * ((pose_then.x_ - pose_now.x_) * cos(delta_w) + (pose_then.y_ - pose_now.y_) * sin(delta_w));
    cmd_->vn_ = PL * ((pose_then.y_ - pose_now.y_) * cos(delta_w) + (pose_then.x_ - pose_now.x_) * sin(delta_w));
    cmd_->vw_ = PW * delta_w;
}

