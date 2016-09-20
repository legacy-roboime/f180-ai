#include "intel.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include "env/segment.h"
#define TARGET RAND_VEC
using namespace std;

bool cmp_segments(const Segment s1, const Segment s2){
  return s1.down < s2.down;
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
  INFINITE = Vec3( 5.0f , 5.0f , 0.0f );
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
  char previous_ref_state;
  float new_target = 0.0f;
  while (true){
    stateIO();
    vector<Robot> our_robots;
    vector<Robot> their_robots;
    int robot_count_player;
    cin >> robot_count_player;

    int   closer_one_id;
    int   second_closer_id;
    int   third_closer_id;
    float min_dist = 1e99;
    float min2_dist = 1e99;
    float min3_dist = 1e99;

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
      } else if (current_dist < min3_dist){
        min3_dist = current_dist;
        third_closer_id = robot_id;
      }
    }
    int robot_count_opponent;
    cin >> robot_count_opponent;

    float min_dist_enemy = 1e99;
    int   closer_enemy_id;

    for (int i = 0; i < robot_count_opponent; ++i) {
      int robot_id;
      float robot_x, robot_y, robot_w, robot_vx, robot_vy, robot_vw;

      cin >> robot_id >> robot_x >> robot_y >> robot_w >> robot_vx >> robot_vy >> robot_vw;
      their_robots.push_back(Robot(Vec3(robot_x,robot_y,robot_w), Vec3(robot_vx, robot_vy, robot_vw), robot_id, false));
      const float current_dist = util::dist2(our_robots.back().getPose(), ball_.pose_);
      if (current_dist < min_dist){
        min_dist_enemy = current_dist;
        closer_enemy_id = robot_id;
      }
    }
    float best_y;
    for (int i = 0; i < our_robots.size() ; ++i){
      const int robot_id = our_robots.at(i).getId();
      if (test_goalie_) {
        if (i == 0) {
            our_robots.at(i).setStance(GOALIE);
        } else {
            our_robots.at(i).setStance(GOAWAY);
        }
      } else if (test_attacker_) {
        if (i == 0) {
            our_robots.at(i).setStance(ATTACKER);
            our_robots.at(i).setClosest(true);
            best_y = this->attackerBestY(ball_.pose_, ssl_geometry_.field_length*0.5, their_robots, -1);
        } else {
            our_robots.at(i).setStance(GOAWAY);
        }
      } else {
        if(closer_one_id != state_.goalie_id_player){
          if (robot_id == state_.goalie_id_player){
            our_robots.at(i).setStance(GOALIE);
          } else if(robot_id == closer_one_id){
            our_robots.at(i).setStance(ATTACKER);
            our_robots.at(i).setClosest(true);
          } else if (robot_id == second_closer_id){
            our_robots.at(i).setStance(ATTACKER);
            our_robots.at(i).setClosest(false);
          } else {
            our_robots.at(i).setStance(DEFENDER);
          }
        } else {
           if (robot_id == state_.goalie_id_player){
            our_robots.at(i).setStance(GOALIE);
          } else if(robot_id == second_closer_id){
            our_robots.at(i).setStance(ATTACKER);
            our_robots.at(i).setClosest(true);
          } else if (robot_id == third_closer_id){
            our_robots.at(i).setStance(ATTACKER);
            our_robots.at(i).setClosest(false);
          } else {
            our_robots.at(i).setStance(DEFENDER);
          }
        }
      }
    }
    cout << state_.counter << endl;
    int def_counter = 0;
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<float> rand(-ssl_geometry_.goal_width*0.5, ssl_geometry_.goal_width*0.5);
    if (previous_ref_state != state_.referee_state){
      new_target = rand(mt);
    }
    const Vec3 RAND_VEC(ssl_geometry_.field_length*0.5, new_target, 0.0f);
    for(int i = 0 ; i < our_robots.size(); ++i){
    Robot mr_robot = our_robots.at(i);
    const int robot_id = our_robots.at(i).getId();
        switch(state_.referee_state){
          case 'N':{
            switch(mr_robot.getStance()){
              case ATTACKER:{
                cerr << best_y << endl;
                const Vec3 GAP_VEC(ssl_geometry_.field_length*0.5, best_y, 0.0f );
                mr_robot.runAttackerAction(ball_.pose_, GAP_VEC, ball_.vel_);
              }
              break;
              case DEFENDER:{
                const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
                if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
                else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                def_counter ++;
              }
              break;
              case GOALIE:{
                float min_dist = 1e20;
                Vec3 closest_robot;
                float y;
                for( auto aux_robot : their_robots) {
                  if(aux_robot.getPose().dist(ball_.pose_) < min_dist) {
                    closest_robot = aux_robot.getPose();
                    min_dist=aux_robot.getPose().dist(ball_.pose_);
                  }
                }
                if(fabs(closest_robot.x-ball_.pose_.x) < EPS) y=mr_robot.getPose().y;
                else y=closest_robot.y-(closest_robot.y-ball_.pose_.y)*(closest_robot.x+ssl_geometry_.field_length/2-0.1)/(closest_robot.x-ball_.pose_.x);
                y = util::clamp(y,-ssl_geometry_.goal_width/2, ssl_geometry_.goal_width/2);
                mr_robot.goToAiming( Vec3(-ssl_geometry_.field_length/2+0.1,y,0), ball_.pose_ );
              }
              break;
              case GOAWAY:{
                mr_robot.goToAiming(INFINITE, Vec3());
              }
              break;
            }
          }
          break;
          case 'S':
          break;
          case 'A': // AVOID
          break;
          case 'p': // PRE_KICKOFF
            mr_robot.goToAiming(mr_robot.getPose(), Vec3 ( 0.0f, 0.0f , 0.0f ));
          break;
          case 'P': // OPPONENT_PRE_KICKOFF
          break;
          case 'K':{ // KICKOFF
            switch(mr_robot.getStance()){
              case ATTACKER:{
                mr_robot.goToAiming(mr_robot.getPose(), Vec3 ( 0.0f, 0.0f , 0.0f ));
              } break;
              case DEFENDER:{
                const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
                if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
                else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                def_counter ++;
              } break;
              case GOALIE:{
                float min_dist = 1e20;
                Vec3 closest_robot;
                float y;
                for( auto aux_robot : their_robots) {
                  if(aux_robot.getPose().dist(ball_.pose_) < min_dist) {
                    closest_robot = aux_robot.getPose();
                    min_dist=aux_robot.getPose().dist(ball_.pose_);
                  }
                }
                if(fabs(closest_robot.x-ball_.pose_.x) < EPS) y=mr_robot.getPose().y;
                else y=closest_robot.y-(closest_robot.y-ball_.pose_.y)*(closest_robot.x+ssl_geometry_.field_length/2)/(closest_robot.x-ball_.pose_.x);
                y = util::clamp(y,-ssl_geometry_.goal_width/2, ssl_geometry_.goal_width/2);
                mr_robot.goToAiming( Vec3(-ssl_geometry_.field_length/2+0.1,y,0), ball_.pose_  );
              }
              break;
              case GOAWAY:{
                mr_robot.goToAiming(INFINITE, Vec3());
              }
              break;
            }
          }
          break;
          case 'k': // OPPONENT_KICKOFF
            if (mr_robot.getStance() == GOAWAY) {
              mr_robot.goToAiming(INFINITE, Vec3());
            }
            break;
          case 'i':{ // INDIRECT
            switch(mr_robot.getStance()){
              case ATTACKER:{
              }
              break;
              case GOAWAY:{
                mr_robot.goToAiming(INFINITE, Vec3());
              }
              break;
              case DEFENDER:{
                const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
                if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
                else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                def_counter ++;
              }
              break;
              case GOALIE:{
                float min_dist = 1e20;
                Vec3 closest_robot;
                float y;
                for( auto aux_robot : their_robots) {
                  if(aux_robot.getPose().dist(ball_.pose_) < min_dist) {
                    closest_robot = aux_robot.getPose();
                    min_dist=aux_robot.getPose().dist(ball_.pose_);
                  }
                }
                if(fabs(closest_robot.x-ball_.pose_.x) < EPS) y=mr_robot.getPose().y;
                else y=closest_robot.y-(closest_robot.y-ball_.pose_.y)*(closest_robot.x+ssl_geometry_.field_length/2)/(closest_robot.x-ball_.pose_.x);
                y = util::clamp(y,-ssl_geometry_.goal_width/2, ssl_geometry_.goal_width/2);
                mr_robot.goToAiming( Vec3(-ssl_geometry_.field_length/2+0.1,y,0), ball_.pose_  );
              }
              break;
            }
          }
          break;
          case 'I':{ // OPPONENT_INDIRECT
            switch(mr_robot.getStance()){
              case ATTACKER:{
              }
              break;
              case GOAWAY:{
                mr_robot.goToAiming(INFINITE, Vec3());
              }
              break;
              case DEFENDER:{
                const float ball_angle = util::aim(OUR_GOAL, ball_.pose_ );
                if( def_counter == 0 ) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle,ball_angle), Vec3(0,0,ball_angle) );
                else if (def_counter == 1) mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle + (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                else mr_robot.goToAiming( OUR_GOAL+util::rec(.09+ssl_geometry_.defense_stretch/2+ssl_geometry_.defense_radius, ball_angle - (10.0f*PI/180) , ball_angle ), Vec3(0,0,ball_angle) );
                def_counter ++;
              }
              break;
              case GOALIE:{
                float min_dist = 1e20;
                Vec3 closest_robot;
                float y;
                for( auto aux_robot : their_robots) {
                  if(aux_robot.getPose().dist(ball_.pose_) < min_dist) {
                    closest_robot = aux_robot.getPose();
                    min_dist=aux_robot.getPose().dist(ball_.pose_);
                  }
                }
                if(fabs(closest_robot.x-ball_.pose_.x) < EPS) y=mr_robot.getPose().y;
                else y=closest_robot.y-(closest_robot.y-ball_.pose_.y)*(closest_robot.x+ssl_geometry_.field_length/2)/(closest_robot.x-ball_.pose_.x);
                y = util::clamp(y,-ssl_geometry_.goal_width/2, ssl_geometry_.goal_width/2);
                mr_robot.goToAiming( Vec3(-ssl_geometry_.field_length/2+0.1,y,0), ball_.pose_ );
              }
              break;
            }
          }
          break;
          case 'd': // DIRECT
          break;
          case 'D': // OPPONENT_DIRECT
          break;
          case 'x': // PRE_PENALTY
          break;
          case 'X': // OPPONENT_PRE_PENALTY
          break;
          case 'y': // PENALTY
          break;
          case 'Y': // OPPONENT_PENALTY
          break;
    }
    mr_robot.getCommand().print();
    }
    previous_ref_state = state_.referee_state;
  }
}


// goalieCost reckons the goal vertical extension not covered by the goalie.
// This function is used to determine where the goalie must be to cover a larger area of the goal.
float Intel::goalieCost( const Vec3 ball_pos, const Vec3 goalie_pos ){
  const float theta = atan2((ball_pos.y-goalie_pos.y), (ball_pos.x-goalie_pos.x));
  const float alpha = asin(0.09f/ball_pos.dist(goalie_pos));
  float y1, y2;
  y1 = ball_pos.y - tan(theta+alpha)*(ssl_geometry_.field_length*0.5f + ball_pos.x);
  y2 = ball_pos.y - tan(theta-alpha)*(ssl_geometry_.field_length*0.5f + ball_pos.x);
  if (y1<y2){
    swap(y1,y2);
  }
  if ((y1 > ssl_geometry_.goal_width*0.5) && (y2 > ssl_geometry_.goal_width*0.5)){y1=y2;} // only to ensure their diff is zero
  else if ((y1 > ssl_geometry_.goal_width*0.5) && (y2 > ssl_geometry_.goal_width*0.5)){y1=y2;}
  else {
  if (y1 > ssl_geometry_.goal_width*0.5){
    y1 = ssl_geometry_.goal_width*0.5;
  }
  if (y2 < -ssl_geometry_.goal_width*0.5){
    y2 = -ssl_geometry_.goal_width*0.5;
  }
  }
  return (ssl_geometry_.goal_width-(y1-y2));
}

// This function returns a point with minimal goalie cost value:
Vec3 Intel::calcMinCost(const Vec3 ball_pos){
  const float x_precision = 0.02;
  const float y_precision = 0.02;
  float min_val = 1e20;
  float min_x, min_y;
  float x,y;
  x = y = 0;
  const float radius = ssl_geometry_.defense_radius-0.09f;
  for (int i = 1 ; x < (ssl_geometry_.defense_radius-0.09f) ; ++i){
    y = 0.5f*(ssl_geometry_.defense_stretch) + radius*sin(acos(x/radius));
    for (int j = 1 ; y > -(0.5f*ssl_geometry_.defense_stretch + radius*sin(acos(x/radius))); ++j){
      const float current_g = goalieCost(ball_pos,Vec3(x-0.5f*ssl_geometry_.field_length,y,0.0f));
      if (current_g < min_val){
        min_val = current_g;
        min_x = x;
        min_y = y;
      }
      y=0.5f*ssl_geometry_.defense_stretch+radius*sin(acos(x/radius)) - y_precision*j;
    }
    x=x_precision*i;
  }
  return Vec3(-0.5f*ssl_geometry_.field_length+min_x, min_y , 0.0f);
}
// Mind the gap. Returns the middle of the larger gap based on shadows the robots do on
float Intel::attackerBestY( const Vec3 ball_pos, const float goal_x, vector<Robot> robots, const int atk_id ){
  vector<Segment> segments;
  for (int i = 0; i < robots.size() ; ++i){ // loop for calculating segments
    auto robot = robots.at(i);
    Vec3 each_pos = robots.at(i).getPose();
    if (robot.getId() == atk_id) { continue; }
//    if (robot.getId() != state_.goalie_id_opponent) { continue; }
//    if ((each_pos.x-goal_x)/*0.09*/ > (ball_pos.x-goal_x)) { continue; } // ignore robots behind ball
    const float theta = atan2(-(ball_pos.y-each_pos.y), -(ball_pos.x-each_pos.x));
    const float alpha = asin(0.09f/ball_pos.dist(each_pos));
    float y1, y2;
    y1 = ball_pos.y + tan(theta+alpha)*(goal_x - ball_pos.x);
    y2 = ball_pos.y + tan(theta-alpha)*(goal_x - ball_pos.x);
    if (y1<y2){
      swap(y1,y2);
    }
    if ((y1 > ssl_geometry_.goal_width*0.5) && (y2 > ssl_geometry_.goal_width*0.5)){ continue; }
    else if ((y1 < -ssl_geometry_.goal_width*0.5) && (y2 < -ssl_geometry_.goal_width*0.5)){ continue; }
    else { // Set segments on goal range
    if (y1 > ssl_geometry_.goal_width*0.5){
      y1 = ssl_geometry_.goal_width*0.5;
    }
    if (y2 < -ssl_geometry_.goal_width*0.5){
      y2 = -ssl_geometry_.goal_width*0.5;
    }
    segments.push_back(Segment(y1,y2));
    }
  }
  // Sort and merge segments
  sort(segments.begin(), segments.end(), cmp_segments); // sort in decreasing order
  stack<Segment> merged_segments;
  if (!segments.empty()) { merged_segments.push(segments.at(0));}
  for (int i = 1; i < segments.size() ; ++i){
    Segment top = merged_segments.top();
    if (top.up < segments.at(i).down){
      merged_segments.push(segments.at(i));
    } else if ( top.up < segments.at(i).up  ){
      top.up = segments.at(i).up;
      merged_segments.pop();
      merged_segments.push(top);
    }
  }
  // Find gaps out of merged intervals
  stack<Segment> gaps;
  float upper = ssl_geometry_.goal_width*0.5f;
  float down = -ssl_geometry_.goal_width*0.5f;
  for (int i = 0 ; i < merged_segments.size() ; ++i){
    gaps.push(Segment(upper, merged_segments.top().up));
    upper = merged_segments.top().down;
  }
  gaps.push(Segment(upper, down));
  float final_result = 0;
  float max_gap = -1e99;
  float max_ang = -1e99;
#if 0
  while (!gaps.empty()){
    const float now_gap = gaps.top().up - gaps.top().down;
    if (now_gap > max_gap){
      min_gap = now_gap;
      final_result = gaps.top().down + now_gap*0.5f;
    }
    gaps.pop();
  }
#else
  while (!gaps.empty()){
    const Vec3 vec1(goal_x-ball_pos.x, gaps.top().up, 0.0f);
    const Vec3 vec2(goal_x-ball_pos.x, gaps.top().down, 0.0f);
    const float now_angle = vec1.ang(vec2);
    if (now_angle > max_ang){
      max_ang = now_angle;
      final_result = gaps.top().down + (gaps.top().up - gaps.top().down)*0.5f;
    }
    gaps.pop();
  }
#endif
  return final_result;
}

