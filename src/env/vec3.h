#pragma once

struct Vec3{
	float x_,y_,w_;

	Vec3(float x, float y, float w):
		x_(x), y_(y), w_(w) {};

	Vec3() : x_(0.0f), y_(0.0f), w_(0.0f){};
};
