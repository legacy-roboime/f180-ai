#pragma once

struct State{
    int         counter_;
    float       timestamp_;
    char        referee_state_;
    float       referee_time_left_;
    int         score_player_, score_opponent_;
    int         goalie_id_player_, goalie_id_opponent_;
    
    State() = default;
    State(int p1, float p2, char p3, float p4, int p5, int p6, int p7, int p8):
        counter_(p1),
        timestamp_(p2),
        referee_state_(p3),
        referee_time_left_(p4),
        score_player_(p5), score_opponent_(p6),
        goalie_id_player_(p7), goalie_id_opponent_(p8) {};
};
