#pragma once

struct Geometry{
  float field_length;
  float field_width;
  float goal_width;
  float center_circle_radius;
  float defense_radius;
  float defense_stretch;

  Geometry() = default;
  Geometry(float p1, float p2, float p3, float p4, float p5, float p6):
    field_length(p1),
    field_width(p2),
    goal_width(p3),
    center_circle_radius(p4),
    defense_radius(p5),
    defense_stretch(p6) {};
};

