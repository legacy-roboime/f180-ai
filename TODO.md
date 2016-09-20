TODO
----

- [ ] OMPL implementation
- [ ] Set a non-outlaw demo for each referee state
- [ ] Potential field implementation
  - [ ] Follow avoid rules
  - [ ] Set indirect (both team and opponent)
  - [ ] Set Kickoff
- [x] Rotation around method enhance (to really describe a circular track)
- [ ] Goalie-player control distinction (not priority)
- [ ] Attacker
    - [x] Best shooting angle algorithm
    - [ ] Strat for no enemy goal gap unavailable
    - [ ] Set backer strat (deflector maybe?)
- [ ] Goalie
    - [x] Algorithm for minimizing available goal area within defense zone
    - [x] Algorithm taking into account other robots in the middle (at least defenders)
    - [ ] Set to goalie act like an attacker when alone with ball in great area
- [ ] Defender
    - [x] Set other defenders to stand in formation (across an arc or across tangent line)

BUGS
----

- [ ] Attacker kicking bug (not progressing in kickoff)
