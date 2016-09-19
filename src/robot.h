#pragma once
#include "env/vec3.h"
#include "ctrl/pid.h"
#include "ctrl/pidrot.h"
#include "ctrl/command.h"
#include "intel.h"

//! Robot class holds methods in which is defined
//! how the robot interacts with the environment and
//! thus changes his state in it.

enum Stance{
  ATTACKER,
  DEFENDER,
  GOALIE,
  GOAWAY
};

enum Attacker_action{
  GOING,
  SETTING,
  TARGETING,
  SHOOTING
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
  bool isAiming( const Vec3 pose ) const; //NOTE: copy w is useless

  void setId( int id );
  void setPose( Vec3 pose );
  void setInput( Vec3 pose, Vec3 vel, int id );
  void setStance( Stance stance );
  void setClosest( bool is_closest );

  void runAttackerAction(const Vec3 ball, const Vec3 target, const Vec3 ball_vel);

  void goToAiming( const Vec3 pose, const Vec3 target );
  void rotateAround( const Vec3 center , const Vec3 target, const float radius);
  void rotateAround( const Vec3 center , const Vec3 target, const Vec3 center_speed );
  void rotateAround( const Vec3 center , const Vec3 target, const Vec3 center_speed , const float radius);
  void setKick( float kick );
  void setDribble( bool dribble );
private:
  Stance stance_;
  Attacker_action action_;
  int id_;
  bool is_friend_;
  bool is_closest_;
  PID pid_;
  Command cmd_;
  Vec3 pose_,vel_;
};
