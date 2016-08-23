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

void Intel::loop(){
    while (true) {
    // State 
    vector<int> ids;
    float x = 0.0f, y = 0.0f, w = 0.0f;
    float tx = 0.0f, ty = 0.0f, tw = 0.0f;
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
    state_ = State(counter, timestamp, referee_state, referee_time_left, score_player, score_opponent, goalie_id_player, goalie_id_opponent);

    float ball_x, ball_y, ball_vx, ball_vy;

    cin >> ball_x >> ball_y >> ball_vx >> ball_vy;
    Ball ball(Vec3 (ball_x, ball_y, 0.0f) , Vec3(ball_vx, ball_vy, 0.0f));
    
    int robot_count_player;
    cin >> robot_count_player;
    vector<Robot> our_robots;
    for (int i = 0; i < robot_count_player; ++i) {
        int robot_id;
        float robot_x, robot_y, robot_w, robot_vx, robot_vy, robot_vw;

        cin >> robot_id >> robot_x >> robot_y >> robot_w >> robot_vx >> robot_vy >> robot_vw;
        ids.push_back(robot_id);
        our_robots.push_back(Robot(Vec3(robot_x,robot_y,robot_w), Vec3(robot_vx, robot_vy, robot_vw), robot_id, true));
        if (robot_id == 0) {
            x = robot_x;
            y = robot_y;
            w = robot_w;
        }
    }

    int robot_count_opponent;
    cin >> robot_count_opponent;
    vector<Robot> their_robots;
    for (int i = 0; i < robot_count_opponent; ++i) {
        int robot_id;
        float robot_x, robot_y, robot_w, robot_vx, robot_vy, robot_vw;

        cin >> robot_id >> robot_x >> robot_y >> robot_w >> robot_vx >> robot_vy >> robot_vw;
        their_robots.push_back(Robot(Vec3(robot_x,robot_y,robot_w), Vec3(robot_vx, robot_vy, robot_vw), robot_id, false));
    }

    tx = ball_x;
    ty = ball_y;
    tw = 0.0f;

    cout << counter << endl;

    for (int i = 0; i < ids.size() ; ++i) {
        const int   robot_id = ids[i];
        float       v_tangent = 0.0f;
        float       v_normal = 0.0f;
        float       v_angular = 0.0f;
        float       kick_force = 0.0f;
        float       chip_force = 0.0f;
        bool        dribble = false;
        Command cmd(v_tangent, v_normal, v_angular, kick_force, chip_force, dribble);

        if (robot_id == 0) {
            PID pid(cmd);
            pid.calcProportional( Vec3(x,y,w), Vec3( tx,ty,util::aim(Vec3(x,y,w) , Vec3(ssl_geometry_.field_length_, 0.0f, 0.0f))));
            cmd.kick_ = 7.0f;
            cmd.dribble_ = false;
        }
        cmd.print();
        }        
    }
}
