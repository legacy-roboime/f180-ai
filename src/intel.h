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
    ~Intel() = default;

    void geometryInput();
    void stateIO();
    void loop();  

    Geometry getGeometry() const { return ssl_geometry_; }
    State getState() const { return state_; }
private:
    Geometry ssl_geometry_;
    State state_;
    Ball ball_;
};

static Vec3 ENEMY_GOAL;
static Vec3 OUR_GOAL;
static Vec3 TOP_MID;
