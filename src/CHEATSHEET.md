# CHEATSHEET

some quick references so we do not need to browse it everytime

- `REFEREE_STATE`: a char, indicates the referee state, one of the following:
    - `S`: __STOP__, stay at least 0.5m away from the ball
    - `N`: __NORMAL__, go wild, score goals
    - `A`: __AVOID__, go wild, score goals, except the indicated robot must not touch the ball
    - `p`: __PRE\_KICKOFF__, return to your field, you will kickoff shortly
    - `k`: __KICKOFF__, you are authorized to kickoff now
    - `i`: __INDIRECT__, kick the ball to resume the game, no double touches or direct goals allowed
    - `d`: __DIRECT__, kick the ball to resume the game, no double touches allowed
    - `x`: __PRE\_PENALTY__, get your robots behind the "penalty line", wait for the order to shoot
    - `y`: __PENALTY__, you may shoot the penalty, and you better score it
    - `P`: __OPPONENT\_PRE_KICKOFF__, return to your field, the opponent will kickoff shortly
    - `K`: __OPPONENT\_KICKOFF__, the opponent is authorized to kickoff, you must still stay away from the ball until the state returns to normal
    - `I`: __OPPONENT\_INDIRECT__, the opponent must kick the ball to resume the play, wait for the normal state to approach the ball
    - `D`: __OPPONENT\_DIRECT__, the opponent must kick the ball to resume the play, wait for the normal state as per above
    - `X`: __OPPONENT\_PRE_PENALTY__, get your robots ready, the opponent will shoot a penalty shortly
    - `Y`: __OPPONENT\_PENALTY__, the opponent may shoot now, save it
