#include "robot.h"

Robot::Robot(Vec3 pose, Vec3 vel, int id, bool is_friend):
		id_(id), vel_(vel), pose_(pose), is_friend_(is_friend) {};
