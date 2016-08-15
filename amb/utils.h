#pragma once

#include <cmath>

#define PI 3.14159265358979323846

// TODO: move these constants to control dir
const float PW = 1.80f;
const float PL = 1.50f;

// utility functions for the sake of simplicity
namespace util{
    float rad(float deg); 
    float deg(float rad);
    float wrap(float ang);
}

