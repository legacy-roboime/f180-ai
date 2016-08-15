#pragma once

struct Geometry{
   float field_length_;
   float field_width_;
   float goal_width_;
   float center_circle_radius_;
   float defense_radius_;
   float defense_stretch_;

   Geometry(float p1, float p2, float p3, float p4, float p5, float p6):
   field_length_(p1),
   field_width_(p2),
   goal_width_(p3),
   center_circle_radius_(p4),
   defense_radius_(p5),
   defense_stretch_(p6) {};
};
