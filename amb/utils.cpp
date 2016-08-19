#include "utils.h"

float util::rad(const float deg) {
    return (PI*deg/180.0);
}

float util::deg(const float rad) {
    return (180.0*rad/PI);
}

float util::wrap(const float ang) {
    return (fmod(ang + 5 * PI, 2 * PI) - PI);
}

float util::dist(const Pose p1, const Pose p2) {
    const float dx_2 = (p1.x_-p2.x_)*(p1.x_-p2.x_);
    const float dy_2 = (p1.y_-p2.y_)*(p1.y_-p2.y_);
    return sqrt(dx_2+dy_2);
}

