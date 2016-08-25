#include "intel.h"
using namespace std;
Intel::Intel(std::vector<Robot> our_robots, std::vector<Robot> their_robots){
    
}
/*
void Intel::setGeometry ( Geometry ssl_geometry ){
    ssl_geometry_ = ssl_geometry;
}

void Intel::setState ( State state ){
    state_ = state;
}*/

void Intel::geometryInput(){ 
    float field_length;
    float field_width;
    float goal_width;
    float center_circle_radius;
    float defense_radius;
    float defense_stretch;

    cin >> field_length
        >> field_width
        >> goal_width
        >> center_circle_radius
        >> defense_radius
        >> defense_stretch;

    cerr << "initialized" << endl;
    ssl_geometry_ = Geometry(field_length, field_width, goal_width, center_circle_radius, defense_radius, defense_stretch); 
}

void Intel::stateIO(){
   // Input
    int     counter;
    float   timestamp;
    char    referee_state;
    float   referee_time_left;
    int     score_player, score_opponent;
    int     goalie_id_player, goalie_id_opponent;
    
    cin >> counter
        >> timestamp
        >> referee_state >> referee_time_left
        >> score_player >> score_opponent
        >> goalie_id_player >> goalie_id_opponent;
    
    state_ = State(counter,
                  timestamp,
                  referee_state,
                  referee_time_left,
                  score_player, score_opponent,
                  goalie_id_player,
                  goalie_id_opponent);

    float ball_x, ball_y, ball_vx, ball_vy;
    cin >> ball_x >> ball_y >> ball_vx >> ball_vy;
    ball_ = Ball(Vec3 (ball_x, ball_y, 0.0f) , Vec3(ball_vx, ball_vy, 0.0f));
    
}

void Intel::loop(){
    while (true) {    
    stateIO();
    vector<Robot> our_robots;
    vector<Robot> their_robots;
    int robot_count_player;
    cin >> robot_count_player;
    for (int i = 0; i < robot_count_player; ++i) {
        int robot_id;
        float robot_x, robot_y, robot_w, robot_vx, robot_vy, robot_vw;

        cin >> robot_id >> robot_x >> robot_y >> robot_w >> robot_vx >> robot_vy >> robot_vw;
        our_robots.push_back(Robot(Vec3(robot_x,robot_y,robot_w), Vec3(robot_vx, robot_vy, robot_vw), robot_id, true));
   }

    int robot_count_opponent;
    cin >> robot_count_opponent;
    for (int i = 0; i < robot_count_opponent; ++i) {
        int robot_id;
        float robot_x, robot_y, robot_w, robot_vx, robot_vy, robot_vw;

        cin >> robot_id >> robot_x >> robot_y >> robot_w >> robot_vx >> robot_vy >> robot_vw;
        their_robots.push_back(Robot(Vec3(robot_x,robot_y,robot_w), Vec3(robot_vx, robot_vy, robot_vw), robot_id, false));
    }
    cout << state_.counter_ << endl;

 
    for (int i = 0; i < our_robots.size() ; ++i) {
        const int robot_id = our_robots.at(i).getId();
        if (robot_id == 0) {
            our_robots.at(i).goToAiming(Vec3(2.0f, 3.0f, 0.0f), Vec3(-ssl_geometry_.field_length_, 0.0f, 0.0f) );
            our_robots.at(i).setKick(7.0f);
        }
        our_robots.at(i).getCommand().print();
        our_robots.at(i).getCommand().printerr();
        }        
    }
}
