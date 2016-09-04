#include "intel.h"
#define TARGET OUR_GOAL 
using namespace std;

Intel::Intel(std::vector<Robot> our_robots, std::vector<Robot> their_robots){
    
}

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
    ENEMY_GOAL = Vec3(field_length*0.5f, 0.0f, 0.0f);
    OUR_GOAL = Vec3(-field_length*0.5f, 0.0f, 0.0f);
    TOP_MID = Vec3(0.0f, field_width*0.5f, 0.0f);
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
    while (true){
    stateIO();
    vector<Robot> our_robots;
    vector<Robot> their_robots;
    int robot_count_player;
    cin >> robot_count_player;

    int def_counter = 0;
    int closer_one_id;
    int second_closer_id;
    float min_dist = 1e99;
    float min2_dist = 1e99;
    for (int i = 0; i < robot_count_player; ++i) {
        int robot_id;
        float robot_x, robot_y, robot_w, robot_vx, robot_vy, robot_vw;
        
        cin >> robot_id >> robot_x >> robot_y >> robot_w >> robot_vx >> robot_vy >> robot_vw;
        our_robots.push_back(Robot(Vec3(robot_x,robot_y,robot_w), Vec3(robot_vx, robot_vy, robot_vw), robot_id, true));
        const float current_dist = util::dist2(our_robots.back().getPose(), ball_.pose_);
        if (current_dist < min_dist){
            min_dist = current_dist;
            closer_one_id = robot_id;
        } else if (current_dist < min2_dist){
            min2_dist = current_dist;
            second_closer_id = robot_id;
        }
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

    int middle_def_id;
    switch(state_.referee_state_){
        case 'N':{
            for (int i = 0; i < our_robots.size() ; ++i) {
                Robot mr_robot = our_robots.at(i);
                const int robot_id = our_robots.at(i).getId();
                if(robot_id == closer_one_id){
                    mr_robot.setStance(ATTACKER);
                    mr_robot.setClosest(true);
                } else if (robot_id == second_closer_id){
                    mr_robot.setStance(ATTACKER);
                    mr_robot.setClosest(false);
                } else if (robot_id == state_.goalie_id_player_){
                    mr_robot.setStance(NONE);
                } 
                else {
                    mr_robot.setStance(DEFENDER);
                    if(def_counter == 0){
                      middle_def_id = robot_id;  
                    }
                    def_counter++;
                }
                int defsign = - 1;
                switch(mr_robot.getStance()){
                   case ATTACKER:{
                        if(mr_robot.isClosest()){
                            const float current_dist = util::dist2(mr_robot.getPose(), ball_.pose_);
                            if(current_dist >= 0.20f*0.20f){ // Arbitrary value
                                mr_robot.goToAiming(ball_.pose_, ball_.pose_);
                            } else {
                                if(!mr_robot.isAiming(ball_.pose_)) {
                                    cerr << "NOT AIMING" << endl;
                                    mr_robot.goToAiming(mr_robot.getPose(), ball_.pose_);
                                } else if(!mr_robot.isAiming(TARGET)) {
                                    cerr << "ROTATING" << endl;
                                    mr_robot.rotateAround(ball_.pose_, TARGET);
                                } else {
                                    cerr << "AIMING" << endl;
                                    mr_robot.goToAiming(ball_.pose_, TARGET);
                                    mr_robot.setKick(5.0f);
                                }
                            }
                        } else {
                        //    mr_robot.goToAiming(Vec3(-3.0f,2.0f,0.0f), ENEMY_GOAL);
                        }
                    }
                    break;
#if 0
                    case DEFENDER:{
                        if(def_counter != 0){
                            if(robot_id == middle_def_id){
                              mr_robot.goToAiming(ENEMY_GOAL*(-1)+Vec3(0.8f,0.0f,0.0f), ball_.pose_); // magic
                            } else {
                            mr_robot.goToAiming(ENEMY_GOAL*(-1)+Vec3(0.8f,0.5*defsign,0.0f), ball_.pose_); // magic
                            }
                            defsign*= (-1);
                            def_counter--;
                        }
                    }
                    break;
                    case NONE:{
                        mr_robot.goToAiming(ENEMY_GOAL*(-1), ball_.pose_);
                        break;
                    }
                    break;
#endif 
                    default:
                    break;
               }
            mr_robot.getCommand().print();
            }
        }
            break;
        case 'S':{
            for (int i = 0; i < our_robots.size() ; ++i) {
                Robot mr_robot = our_robots.at(i);
                const int robot_id = our_robots.at(i).getId();

                if (robot_id == state_.goalie_id_player_){
                    mr_robot.goToAiming(Vec3(-ssl_geometry_.field_length_*0.5, 0.0f, 0.0f), ball_.pose_);
                } else if (mr_robot.isClosest()) {
                    if (!mr_robot.isAiming(ball_.pose_)) {
                        mr_robot.goToAiming(mr_robot.getPose(), ball_.pose_);
                    } else if (!mr_robot.isAiming(ENEMY_GOAL)) {
                        mr_robot.rotateAround(ball_.pose_, ENEMY_GOAL);
                    } else {
                        mr_robot.goToAiming(ball_.pose_, ENEMY_GOAL);
                        mr_robot.setKick(3.0f);
                    }
                    mr_robot.goToAiming(ball_.pose_-util::normalize(ball_.pose_)*0.5f, ball_.pose_);
                } else {

                }
                mr_robot.getCommand().print(); 
            }
        }
            break;
        default:{
            for (int i = 0; i < our_robots.size() ; ++i) {
              Robot mr_robot = our_robots.at(i);
/*                const int robot_id = our_robots.at(i).getId();
                if (robot_id == state_.goalie_id_player_){
                    mr_robot.goToAiming(Vec3(-ssl_geometry_.field_length_*0.5, 0.0f, 0.0f), ball_.pose_);
                }
                if (robot_id == closer_one_id) {
                    mr_robot.goToAiming(ball_.pose_-util::normalize(ball_.pose_)*0.5f, Vec3(ssl_geometry_.field_length_*0.5, 0.0f, 0.0f) );
                    mr_robot.setKick(5.0f);
                }
                if (robot_id == second_closer_id){
                    mr_robot.goToAiming(Vec3(0.0f, 0.0f, 0.0f),  Vec3(ball_.pose_));
                }
                */
                mr_robot.getCommand().print();
            }
        }
            break;
    }
    }
}
    
