#pragma once

//! Vec3 is used in the code for easing operations with entities
//! poses ( cartesian coordinates plus orientation in the field)
//! and for speed triples ( tangent, normal and angular speeds).
//! Due to that, algebraic vectorial operations may only take into
//! account the x and y features of Vec3, since they may describe
//! one's coordinate in a 2D space.

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
    return Vec3 ( val*x_, val*y_, w_ );
  }

  float magnitude();
  float dist(const Vec3 target);
  float dist2(const Vec3 target);
  Vec3 normalize();
};

