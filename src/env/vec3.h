#pragma once

//! Vec3 is used in the code for easing operations with entities
//! poses ( cartesian coordinates plus orientation in the field)
//! and for velocity triples ( tangent, normal and angular velocity).
//! Due to that, standard algebraic vectorial operations take into
//! account only the x and y coordinates of Vec3, since they describe
//! one's coordinate in a 2D space.

struct Vec3{
  float x_,y_,w_;

  ///Constructor
  Vec3(float x, float y, float w):
    x_(x), y_(y), w_(w) {};
  ///Default constructor
  Vec3() : x_(0.0f), y_(0.0f), w_(0.0f){};
  ///Adds two vectors
  Vec3 operator+(const Vec3& vec) const {
    return Vec3( x_ + vec.x_, y_ + vec.y_, w_ );
  }
  ///Subtracts two vectors
  Vec3 operator-(const Vec3& vec) const {
    return Vec3( x_ - vec.x_, y_ - vec.y_, w_ );
  }
  ///Multiplies coordinates by a scalar
  Vec3 operator*(const float val) const { // NOTE: only for coordinates
    return Vec3 ( val*x_, val*y_, w_ );
  }
  ///2D scalar product between two vectors
  float operator*(const Vec3& vec) const {
    return (x_*vec.x_+y_*vec.y_);
  }

  ///Returns vector length
  float length() const ;
  ///Returns distance to target
  float dist(const Vec3 target) const ;
  ///Returns square of distance to target
  float dist2(const Vec3 target) const ;
  ///Returns angle between two 2D vectors
  float ang(const Vec3 vec) const ;
  ///Returns corresponding unit vector
  Vec3 normalized() const ;
};

