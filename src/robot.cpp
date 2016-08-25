#include "robot.h"

Robot::Robot() { //TODO: review setCommandPtr in this;
    pid_.setCommandPtr(cmd_);
}

Robot::Robot(Vec3 pose, Vec3 vel, int id, bool is_friend):
		id_(id), vel_(vel), pose_(pose), is_friend_(is_friend) 
        { pid_.setCommandPtr(cmd_); }

void Robot::setId(int id){
    id_ = id;
}

void Robot::setPose(Vec3 pose){
    pose_ = pose;
}

//TODO: refactor. All we need is the desired pose once we have the angle
void Robot::goToAiming (Vec3 pose, Vec3 target){
    PID pid(cmd_);
    const float aim = util::aim(pose_ , target);
    pid.calcProportional(pose_, Vec3 (pose.x_, pose.y_ , aim));
}

void Robot::setKick(float kick){
    cmd_.kick_ = kick;
    cmd_.dribble_ = false;
}
