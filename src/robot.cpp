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

void Robot::rotateAround(Vec3 const center, Vec3 const target, const float radius){
  float final_angle = util::wrap(center.aim(target)+PI);
  PIDRot pid(cmd_);
  pid.calcProportional(pose_, center, radius, final_angle);
}

void Robot::rotateAround( Vec3  center , Vec3 target, Vec3 center_speed, const float radius ){
  float final_angle = util::wrap(center.aim(target)+PI);
  PIDRot pid(cmd_);
  pid.calcProportional(pose_, center, radius, final_angle);
}

void Robot::runAttackerAction(const Vec3 ball_pos, const Vec3 target, const Vec3 ball_vel){
  if(this->isClosest()){
    const float current_dist = util::dist(pose_, ball_pos);
    if(current_dist >= 0.20f){
      cerr << "going towards ball" << endl;
      this->goToAiming(ball_pos, ball_pos);
    } else {
      if(!(this->isAiming(ball_pos)) || !this->isAiming(target)) {
        cerr << "setting on ball" << endl;
        this->rotateAround(ball_pos, target, 0.15); //! \bug sometimes stopping while rotating
      } else {
        cerr << "gonna kick" << endl;
        this->goToAiming(ball_pos, target);
        this->setKick(5.0f);
      }
    }
  } else {

  }
}

void Robot::runDefenderAction(const Ball ball, const Vec3 goalie_spot, const Geometry& ssl_geometry, const int def_counter){
  const float ball_angle = util::aim(goalie_spot , ball.pose_ );
  if( def_counter == 0 ) {
    this->goToAiming( goalie_spot+util::rec(.09+ssl_geometry.defense_stretch/2+ssl_geometry.defense_radius, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
  } else if (def_counter == 1){
    this->goToAiming( goalie_spot+util::rec(.09+ssl_geometry.defense_stretch/2+ssl_geometry.defense_radius, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
  } else {
  this->goToAiming( goalie_spot+util::rec(.09+ssl_geometry.defense_stretch/2+ssl_geometry.defense_radius, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
  }
}
