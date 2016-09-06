#include "robot.h"
#include <iostream>
using namespace std;

Robot::Robot() { //TODO: review setCommandPtr in this;
    pid_.setCommandPtr(cmd_);
    stance_ = NONE;
}

Robot::Robot(Vec3 pose, Vec3 vel, int id, bool is_friend):
		id_(id), vel_(vel), pose_(pose), is_friend_(is_friend), stance_(NONE)
        { pid_.setCommandPtr(cmd_); } //TODO: debug

void Robot::setId( int id ){
    id_ = id;
}

void Robot::setPose( Vec3 pose ){
    pose_ = pose;
}

void Robot::setStance( Stance stance ){
    stance_ = stance;
}
void Robot::setClosest( bool is_closest ){
    is_closest_ = is_closest;
}

//TODO: refactor. All we need is the desired pose once we have the angle
void Robot::goToAiming (Vec3 pose, Vec3 target){
    PID pid(cmd_);
    const float aim = util::aim(pose_ , target);
    pid.calcProportional(pose_, Vec3 (pose.x_, pose.y_ , aim));
}

bool Robot::isAiming(const Vec3 target) const {
    const float current_angle = util::wrap(pose_.w_);
    const float aim = util::aim(pose_, target);
    const float diff = fabs(current_angle-aim);
    return diff <= PI/180.0f;
}

void Robot::setKick(float kick){
    cmd_.kick_ = kick;
    cmd_.dribble_ = false;
}

void Robot::rotateAround(Vec3 center, Vec3 target){
    const float radius = sqrt(util::dist2(center, pose_));
    const float final_angle = util::aim(center, target);
    Vec3 final_pose(pose_.x_+radius*( cos(pose_.w_) - cos(final_angle) ),
                    pose_.y_+radius*( sin(pose_.w_) - sin(final_angle) ),
                    final_angle);
    PID pid(cmd_);
    pid.calcProportional(pose_, final_pose);
    cmd_.vt_ = 0.0f;
    cmd_.vn_ = -cmd_.vw_*radius;
}

void Robot::rotateAround( Vec3 center , Vec3 target, Vec3 center_speed ){
  const float radius = sqrt(util::dist2(center, pose_));
  const float final_angle = util::aim(center, target);
  const Vec3 transformed_center_speed = Vec3(center_speed.x_*cos(pose_.w_) + center_speed.y_*sin(pose_.w_),center_speed.x_*sin(pose_.w_) - center_speed.y_*cos(pose_.w_), 0.0f);
  const Vec3 final_pose(pose_.x_+radius*( cos(pose_.w_) - cos(final_angle) ),
                    pose_.y_+radius*( sin(pose_.w_) - sin(final_angle) ),
                    final_angle);
  PID pid(cmd_);
  pid.calcProportional(pose_, final_pose);
  cmd_.vt_ = transformed_center_speed.x_;
  cmd_.vn_ = -cmd_.vw_*radius - transformed_center_speed.y_;
}

