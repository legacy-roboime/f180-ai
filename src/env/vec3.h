#pragma once

struct Vec3{
  float x_,y_,w_;

  Vec3(float x, float y, float w):
    x_(x), y_(y), w_(w) {};

  Vec3() : x_(0.0f), y_(0.0f), w_(0.0f){};

  Vec3 operator+(const Vec3& vec) const {
    return Vec3( x_ + vec.x_, y_ + vec.y_, w_ );
  }
  Vec3 operator-(const Vec3& vec) const {
    return Vec3( x_ - vec.x_, y_ - vec.y_, w_ );
  }

  Vec3 operator*(const float val) const { // NOTE: only for coordinates
    Vec3 aux( val*x_, val*y_, w_ );
    return aux;
  }
};

