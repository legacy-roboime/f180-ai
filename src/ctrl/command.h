#pragma once
//ew
class Command {
public:
    Command();
    Command(float vt, float vn, float vw, float kick, float chip, bool dribble);

    void print();
    void printerr();
//private:
    float vt_, vn_, vw_;
    float kick_ , chip_;
    bool dribble_;
};
