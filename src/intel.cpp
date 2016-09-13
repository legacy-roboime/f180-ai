#include "intel.h"
#define TARGET ENEMY_GOAL
using namespace std;

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
  int     referee_more_info;
  int     score_player, score_opponent;
  int     goalie_id_player, goalie_id_opponent;

  cin >> counter
    >> timestamp
    >> referee_state >> referee_more_info
    >> score_player >> score_opponent
    >> goalie_id_player >> goalie_id_opponent;

  state_ = State(
    counter,
    timestamp,
    referee_state,
    referee_more_info,
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
    int def_counter = 0;
    cerr << state_.referee_state_ << endl;
    switch(state_.referee_state_){
      case 'N':{
        for (int i = 0; i < our_robots.size() ; ++i) {
        Robot mr_robot = our_robots.at(i);
        const int robot_id = our_robots.at(i).getId();
        if (robot_id == state_.goalie_id_player_){
          mr_robot.setStance(GOALIE);
        } else if(robot_id == closer_one_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(true);
        } else if (robot_id == second_closer_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(false);
        } else {
           mr_robot.setStance(DEFENDER);
        }
        switch(mr_robot.getStance()){
          case ATTACKER:{
            if(mr_robot.isClosest()){
              const float current_dist2 = util::dist2(mr_robot.getPose(), ball_.pose_);
              if(current_dist2 >= 0.15f*0.15f){
                mr_robot.goToAiming(ball_.pose_, ball_.pose_);
              } else {
                if(!mr_robot.isAiming(ball_.pose_)) {
                  mr_robot.goToAiming(mr_robot.getPose(), ball_.pose_);
              } else if(!mr_robot.isAiming(TARGET)) {
                  mr_robot.rotateAround(ball_.pose_, TARGET, ball_.vel_); //! \bug sometimes stopping while rotating
              } else {
                  mr_robot.goToAiming(ball_.pose_, TARGET);
                  mr_robot.setKick(5.0f);
                }
              }
            } else {
              //set backer strat
            }
          }
          break;
          case DEFENDER:{
            const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
            if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
            else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            def_counter ++;
          }
          break;
          case GOALIE:{
            mr_robot.goToAiming( OUR_GOAL, ball_.pose_ );
          }
          break;
        }
        mr_robot.getCommand().print();
        }
      }
      break;
      case 'S':{
        for (int i = 0; i < our_robots.size() ; ++i){
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
            mr_robot.setKick(4.0f);
          }
          mr_robot.goToAiming(mr_robot.getPose(), ball_.pose_-ball_.pose_.normalized()*0.5f);
          } else {

          }
          mr_robot.getCommand().print();
        }
        break;
      }
      case 'A': // AVOID
      case 'p': // PRE_KICKOFF
      case 'P': // OPPONENT_PRE_KICKOFF
      case 'K':{ // KICKOFF
        for (int i = 0; i < our_robots.size() ; ++i) {
        Robot mr_robot = our_robots.at(i);
        const int robot_id = our_robots.at(i).getId();
        if (robot_id == state_.goalie_id_player_){
          mr_robot.setStance(GOALIE);
        } else if(robot_id == closer_one_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(true);
        } else if (robot_id == second_closer_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(false);
        } else {
           mr_robot.setStance(DEFENDER);
        }
        switch(mr_robot.getStance()){
          case ATTACKER:{
            if(mr_robot.isClosest()){
              const float current_dist2 = util::dist2(mr_robot.getPose(), ball_.pose_);
              if(current_dist2 >= 0.15f*0.15f){
                mr_robot.goToAiming(ball_.pose_, ball_.pose_);
              } else {
                if(!mr_robot.isAiming(ball_.pose_)) {
                  mr_robot.goToAiming(mr_robot.getPose(), ball_.pose_);
              } else if(!mr_robot.isAiming(TARGET)) {
                  mr_robot.rotateAround(ball_.pose_, TARGET, ball_.vel_); //! \bug sometimes stopping while rotating
              } else {
                  mr_robot.goToAiming(ball_.pose_, TARGET);
                  mr_robot.setKick(5.0f);
                }
              }
            } else {
              //set backer strat
            }
          }
          break;
          case DEFENDER:{
            const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
            if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
            else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            def_counter ++;
          }
          break;
          case GOALIE:{
            mr_robot.goToAiming( OUR_GOAL, ball_.pose_ );
          }
          break;
        }
        mr_robot.getCommand().print();
        }
      }
               break;
      case 'k': // OPPONENT_KICKOFF
      case 'i':{ // INDIRECT
        for (int i = 0; i < our_robots.size() ; ++i) {
        Robot mr_robot = our_robots.at(i);
        const int robot_id = our_robots.at(i).getId();
        if (robot_id == state_.goalie_id_player_){
          mr_robot.setStance(GOALIE);
        } else if(robot_id == closer_one_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(true);
        } else if (robot_id == second_closer_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(false);
        } else {
           mr_robot.setStance(DEFENDER);
        }
        switch(mr_robot.getStance()){
          case ATTACKER:{
            if(mr_robot.isClosest()){
              const float current_dist2 = util::dist2(mr_robot.getPose(), ball_.pose_);
              if(current_dist2 >= 0.15f*0.15f){
                mr_robot.goToAiming(ball_.pose_, ball_.pose_);
              } else {
                if(!mr_robot.isAiming(ball_.pose_)) {
                  mr_robot.goToAiming(mr_robot.getPose(), ball_.pose_);
              } else if(!mr_robot.isAiming(TARGET)) {
                  mr_robot.rotateAround(ball_.pose_, TARGET, ball_.vel_); //! \bug sometimes stopping while rotating
              } else {
                  mr_robot.goToAiming(ball_.pose_, TARGET);
                  mr_robot.setKick(5.0f);
                }
              }
            } else {
              //set backer strat
            }
          }
          break;
          case DEFENDER:{
            const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
            if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
            else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            def_counter ++;
          }
          break;
          case GOALIE:{
            mr_robot.goToAiming( OUR_GOAL, ball_.pose_ );
          }
          break;
        }
        mr_robot.getCommand().print();
        }
      }
      break;
      case 'I':{ // OPPONENT_INDIRECT
        for (int i = 0; i < our_robots.size() ; ++i) {
        Robot mr_robot = our_robots.at(i);
        const int robot_id = our_robots.at(i).getId();
        if (robot_id == state_.goalie_id_player_){
          mr_robot.setStance(GOALIE);
        } else if(robot_id == closer_one_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(true);
        } else if (robot_id == second_closer_id){
          mr_robot.setStance(ATTACKER);
          mr_robot.setClosest(false);
        } else {
           mr_robot.setStance(DEFENDER);
        }
        switch(mr_robot.getStance()){
          case ATTACKER:{
            if(mr_robot.isClosest()){
              const Vec3 radial(ball_.pose_.x+ssl_geometry_.field_length_*0.5 , ball_.pose_.y, 0.0f);
              mr_robot.goToAiming(ball_.pose_ - radial.normalized()*0.59f, ball_.pose_);
            } else {
              //set backer strat
            }
          }
          break;
          case DEFENDER:{
            const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
            if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
            else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch_/2+ssl_geometry_.defense_radius_, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
            def_counter ++;
          }
          break;
          case GOALIE:{
            mr_robot.goToAiming( OUR_GOAL, ball_.pose_ );
          }
          break;
        }
        mr_robot.getCommand().print();
        }
      }
      break;
      case 'd': // DIRECT
      case 'D': // OPPONENT_DIRECT
      case 'x': // PRE_PENALTY
      case 'X': // OPPONENT_PRE_PENALTY
      case 'y': // PENALTY
      case 'Y': // OPPONENT_PENALTY
      default:{
        for(int i = 0; i < our_robots.size();i++)
          our_robots.at(i).getCommand().print();
        break;
      }
    }
  }
}

