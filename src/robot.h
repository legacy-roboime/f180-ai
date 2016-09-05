#pragma once
#include "env/vec3.h"
#include "env/utils.h"
#include "ctrl/pid.h"
#include "ctrl/command.h"
#include "intel.h"

//TODO:set inputs to const (review)

enum Stance{
    ATTACKER,
    DEFENDER,
    NONE
};

class Robot{
public:
    Robot();
    Robot( Vec3 pose, Vec3 vel, int id, bool is_friend_ );
    ~Robot() = default;

    int getId() const { return id_; }
    Vec3 getPose() const { return pose_; }
    Vec3 getVel() const { return vel_;  }
    Command getCommand() const { return cmd_;  }
    bool isFriend() const { return is_friend_;  }
    Stance getStance() const { return stance_;  }
    bool isClosest() const { return is_closest_; }
    bool isAiming(const Vec3 pose) const; //NOTE: copy w_ is useless

    void setId( int id );
    void setPose( Vec3 pose );
    void setInput( Vec3 pose, Vec3 vel, int id );
    void setStance( Stance stance );
    void setClosest( bool is_closest );

    void goToAiming( Vec3 pose, Vec3 target );
    void rotateAround( Vec3 center , Vec3 target);
    void setKick( float kick );
    void setDribble( bool dribble );
private:
    Stance stance_;
    int id_;
    bool is_friend_;
    bool is_closest_; // TODO: has ball algorithm
    PID pid_;
    Command cmd_;
    Vec3 pose_,vel_;
};
