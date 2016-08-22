#pragma once
#include "env/vec3.h"

#include "ctrl/pid.h"
#include "ctrl/command.h"

class Robot{
public:
    Robot();
	Robot( Vec3 pose, Vec3 vel, int id );

 	int getId() const { return id_; }
	Vec3 getPose() const { return pose_; }
    Vec3 getVel() const { return vel_;  }

	void setId();
	void setPose();
    void setInput( Vec3 pose, Vec3 vel, int id );

private:
	int id_;
    PID pid_;
    Command cmd_;
    Vec3 pose_,vel_; 
	Robot* robots_allies_;
};
