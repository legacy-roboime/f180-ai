#pragma once

//! Vec3 is used in the code for easing operations with entities
//! poses ( cartesian coordinates plus orientation in the field)
//! and for velocity triples ( tangent, normal and angular velocity).
//! Due to that, standard algebraic vectorial operations take into
//! account only the x and y coordinates of Vec3, since they describe
//! one's coordinate in a 2D space.

struct Vec3{
  float x,y,w;

  ///Constructor
  Vec3(float x, float y, float w):
    x(x), y(y), w(w) {};
  ///Default constructor
  Vec3() : x(0.0f), y(0.0f), w(0.0f){};
  ///Adds two vectors
  Vec3 operator+(const Vec3& vec) const {
    return Vec3( x + vec.x, y + vec.y, w );
  }
  ///Subtracts two vectors
  Vec3 operator-(const Vec3& vec) const {
    return Vec3( x - vec.x, y - vec.y, w );
  }
  ///Multiplies coordinates by a scalar
  Vec3 operator*(const float val) const { // NOTE: only for coordinates
    return Vec3 ( val*x, val*y, w );
  }
  ///2D scalar product between two vectors
  float operator*(const Vec3& vec) const {
    return (x*vec.x+y*vec.y);
  }

  ///Returns vector length
  float length() const ;
  ///Returns distance to target
  float dist(const Vec3 target) const ;
  ///Returns square of distance to target
  float dist2(const Vec3 target) const ;
  ///Returns angle between two 2D vectors
  float ang(const Vec3 vec) const ;
  ///Receives angle in radians and returns angularly displaced Vec3
  Vec3 displaced(const float angle) const ;
  ///Returns corresponding unit vector
  Vec3 normalized() const ;
  ///Returns angle of vector aiming target
  float aim(const Vec3 target) const;
};

