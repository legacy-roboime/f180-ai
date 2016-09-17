#pragma once

struct State{
  int    counter;
  float  timestamp;
  char   referee_state;
  int    referee_more_info;
  int    score_player, score_opponent;
  int    goalie_id_player, goalie_id_opponent;

  State() = default;
  State(int p1, float p2, char p3, float p4, int p5, int p6, int p7, int p8):
    counter(p1),
    timestamp(p2),
    referee_state(p3),
    referee_more_info(p4),
    score_player(p5), score_opponent(p6),
    goalie_id_player(p7), goalie_id_opponent(p8) {};
};
