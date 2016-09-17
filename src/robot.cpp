#include "robot.h"
#include "env/utils.h"
#include <cmath>
#include <iostream>
using namespace std;

Robot::Robot() { //TODO: review setCommandPtr in this;
    pid_.setCommandPtr(cmd_);
    stance_ = GOALIE;
}

Robot::Robot(Vec3 pose, Vec3 vel, int id, bool is_friend):
    id_(id), vel_(vel), pose_(pose), is_friend_(is_friend), stance_(GOALIE)
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

void Robot::goToAiming (Vec3 const pose, Vec3 const target){
    PID pid(cmd_);
    const float aim = util::aim(pose_ , target);
    pid.calcProportional(pose_, Vec3 (pose.x, pose.y , aim));
}

bool Robot::isAiming(const Vec3 target) const {
  const float current_angle = util::wrap(pose_.w);
  const float aim = util::aim(pose_, target);
  const float diff = fabs(current_angle-aim);
  return diff <= PI/180.0f; return diff <= PI/180.0f;
}

void Robot::setKick(float kick){
  cmd_.kick_ = kick;
  cmd_.dribble_ = false;
}

void Robot::rotateAround(Vec3 const center, Vec3 const target){
    const float radius = sqrt(util::dist2(center, pose_));
    const float final_angle = util::aim(center, target);
    Vec3 final_pose(pose_.x+radius*( cos(pose_.w) - cos(final_angle) ),
                    pose_.y+radius*( sin(pose_.w) - sin(final_angle) ),
                    final_angle);
    PID pid(cmd_);
    pid.calcProportional(pose_, final_pose);
    cmd_.vt_ = 0.0f;
    cmd_.vn_ = -cmd_.vw_*radius;
}

void Robot::rotateAround( Vec3  center , Vec3 target, Vec3 center_speed ){
  const float radius = sqrt(util::dist2(center, pose_));
  const float final_angle = util::aim(center, target);
  const Vec3 transformed_center_speed = Vec3(center_speed.x*cos(pose_.w) + center_speed.y*sin(pose_.w),center_speed.x*sin(pose_.w) - center_speed.y*cos(pose_.w), 0.0f);
  const Vec3 final_pose(pose_.x+radius*( cos(pose_.w) - cos(final_angle) ),
                    pose_.y+radius*( sin(pose_.w) - sin(final_angle) ),
                    final_angle);
  PID pid(cmd_);
  pid.calcProportional(pose_, final_pose);
  cmd_.vt_ = transformed_center_speed.x;
  cmd_.vn_ = -cmd_.vw_*radius - transformed_center_speed.y;
}

void Robot::runAttackerAction(const Vec3 ball_pos, const Vec3 target, const Vec3 ball_vel){
  if(this->isClosest()){
  const float current_dist2 = util::dist2(pose_, ball_pos);
  if(current_dist2 >= 0.15f*0.15f){
    cerr << "going towards ball" << endl;
    this->goToAiming(ball_pos, ball_pos);
  } else {
    if(!(this->isAiming(ball_pos))) {
      cerr << "setting on ball" << endl;
      this->goToAiming(pose_, ball_pos);
  } else if(!this->isAiming(target)) {
      cerr << "setting to target" << endl;
      this->rotateAround(ball_pos, target, ball_vel); //! \bug sometimes stopping while rotating
      this->setKick(5.0f);
  } else {
      cerr << "gonna kick" << endl;
      this->goToAiming(ball_pos, target);
      this->setKick(5.0f);
    }
  }
  } else {

  }
}

