#pragma once

struct Pose{
	float x_,y_,w_;

	Pose(float x, float y, float w):
		x_(x), y_(y), w_(w) {};

	Pose() : x_(0.0f), y_(0.0f), w_(0.0f){};
};