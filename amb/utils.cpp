#include "utils.h"

float util::rad(float deg){
    return (PI*deg/180.0);
}

float util::deg(float rad){
    return (180.0*rad/PI);
}

// Set an angle to (-PI,PI) value range
float util::wrap(float ang){
    return (fmod(ang + 5 * PI, 2 * PI) - PI);
}

