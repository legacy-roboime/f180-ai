#include "command.h"
#include <iostream>

using namespace std;

Command::Command(){
   vt_ = 0.0f;
   vn_ = 0.0f;
   vw_ = 0.0f;
   kick_ = 0.0f;
   chip_ = 0.0f;
   dribble_ = false;
}

Command::Command(float vt, float vn, float vw, float kick, float chip, bool dribble){
    vt_ = vt;
    vn_ = vn;
    vw_ = vw;
    kick_ = kick;
    chip_ = chip;
    dribble_ = dribble;
}
Command::Command(Vec3 vel, float kick, float chip, bool dribble){
    vt_ = vel.x_;
    vn_ = vel.y_;
    vw_ = vel.w_;
    chip_ = chip;
    dribble_ = dribble;
}

void Command::print(){
    cout << vt_ << " " << vn_ << " " << vw_ << " " << kick_ << " " << chip_ << " " << dribble_ << endl;
}

void Command::printerr(){
    cerr <<"vt: " << vt_ << " vn: " << vn_ << " vw: " << vw_ << " kick: " << kick_ << " chip: " << chip_ << " dribble? " << dribble_ << endl;
}
