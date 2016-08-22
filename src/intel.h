#pragma once

#include <vector>

#include "robot.h"
#include "env/ssl_geometry"

class Intel{
public:
    Intel() = default;
    ~Intel() = default;
    std::vector<Robot> our_robots;
    std::vector<Robot> their_robots;

    void setGeometry( Geometry geometry );
private:
    Geometry ssl_geometry;
}
