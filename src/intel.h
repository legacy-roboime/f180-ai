#pragma once

#include <vector>

#include "robot.h"
#include "env/ssl_geometry.h"
#include "env/state.h"
class Intel{
public:
    Intel() = default;
    Intel(std::vector<Robot> our_robots, std::vector<Robot> their_robots_);
    ~Intel() = default;
    
    void setGeometry( Geometry geometry );
    void setState( State state );
    Geometry getGeometry() const { return ssl_geometry_; }
    State getState() const { return state_; }
private:
    Geometry ssl_geometry_;
    State state_;
    std::vector<Robot> our_robots_;
    std::vector<Robot> their_robots_;
};
