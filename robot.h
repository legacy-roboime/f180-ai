#pragma once
#include "amb/pose.h"

class Robot{
public:
	Robot(Pose pose, int id);
	~Robot() = delete;

 	int getId() const { return id_; }
	Pose getPose() const { return pose_; }

	void setId();
	void setPose();
	
private:
	int id_;
	Pose pose_;
	Robot* robots_allies_;
};
