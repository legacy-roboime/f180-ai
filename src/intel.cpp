#include "intel.h"
Intel::Intel(std::vector<Robot> our_robots, std::vector<Robot> their_robots){
    
}

void Intel::setGeometry ( Geometry ssl_geometry ){
    ssl_geometry_ = ssl_geometry;
}

void Intel::setState ( State state ){
    state_ = state;
}
