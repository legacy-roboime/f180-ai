#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "robot.h"
#include "env/ssl_geometry.h"
#include "env/state.h"
#include "env/ball.h"
#include "env/utils.h"

class Intel{
public:
    Intel() = default;
    Intel(std::vector<Robot> our_robots, std::vector<Robot> their_robots_);
    ~Intel() = default;

    void geometryInput();
    void loop();  

    Geometry getGeometry() const { return ssl_geometry_; }
    State getState() const { return state_; }
private:
    Geometry ssl_geometry_;
    State state_;
    std::vector<Robot>* our_robots_;
    std::vector<Robot>* their_robots_;
};
