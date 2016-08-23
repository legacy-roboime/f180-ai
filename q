[1mdiff --git a/TODO.md b/TODO.md[m
[1mindex d858e10..324936a 100644[m
[1m--- a/TODO.md[m
[1m+++ b/TODO.md[m
[36m@@ -1,5 +1,6 @@[m
 TODO[m
 ----[m
 [m
[31m-[ ] Geometry input error fix[m
[31m-[ ] Enhance Makefile[m
[32m+[m[32m[ x ] Geometry input error fix[m
[32m+[m[32m[ x ] Enhance Makefile[m
[32m+[m[32m[ ] Solve the "it goes crazy when not aiming goal" bug[m
[1mdiff --git a/src/ctrl/pid.h b/src/ctrl/pid.h[m
[1mindex 1a8b6c9..b91adb9 100644[m
[1m--- a/src/ctrl/pid.h[m
[1m+++ b/src/ctrl/pid.h[m
[36m@@ -13,7 +13,7 @@[m [mpublic:[m
     PID(Command& cmd);[m
     void calcProportional(const Vec3 pose_now, const Vec3 pose_then);[m
 private:[m
[31m-    const float PL = 1.50f; //TODO: friendly names, maybe?[m
[32m+[m[32m    const float PL = 1.30f; //TODO: friendly names, maybe?[m
     const float PW = 1.80f;[m
     Command* cmd_;[m
 };[m
[1mdiff --git a/src/env/utils.cpp b/src/env/utils.cpp[m
[1mindex 79ff5e7..dcc6c6e 100644[m
[1m--- a/src/env/utils.cpp[m
[1m+++ b/src/env/utils.cpp[m
[36m@@ -18,6 +18,12 @@[m [mfloat util::dist(const Vec3 pose1, const Vec3 pose2) {[m
     return sqrt(dx_2+dy_2);[m
 }[m
 [m
[32m+[m[32mfloat util::mod(const float val){[m
[32m+[m[32m    return val>0?val:-val;[m
[32m+[m[32m}[m
[32m+[m
 float util::aim(const Vec3 shooter, const Vec3 target){[m
[31m-   return wrap(atan((shooter.y_ - target.y_) / (shooter.x_ - target.x_)));[m
[32m+[m[32m    const float x = target.x_ - shooter.x_;[m
[32m+[m[32m    const float y = target.y_ - shooter.y_;[m
[32m+[m[32m    return atan2(y,x);[m
 }[m
[1mdiff --git a/src/env/utils.h b/src/env/utils.h[m
[1mindex 2bcab81..0f3fc06 100644[m
[1m--- a/src/env/utils.h[m
[1m+++ b/src/env/utils.h[m
[36m@@ -12,5 +12,6 @@[m [mnamespace util{[m
     float wrap(const float ang) ;[m
     float dist(const Vec3 pose1, const Vec3 pose2);[m
     float aim(const Vec3 shooter, const Vec3 target); //TODO:names[m
[32m+[m[32m    float mod(const float val);[m
 }[m
 [m
[1mdiff --git a/src/intel.cpp b/src/intel.cpp[m
[1mindex 00f8601..def257f 100644[m
[1m--- a/src/intel.cpp[m
[1m+++ b/src/intel.cpp[m
[36m@@ -109,6 +109,7 @@[m [mvoid Intel::loop(){[m
             cmd.dribble_ = false;[m
         }[m
         cmd.print();[m
[32m+[m[32m        cmd.printerr();[m
         }        [m
     }[m
 }[m
[1mdiff --git a/src/intel.h b/src/intel.h[m
[1mindex 9bb6767..6a46ebc 100644[m
[1m--- a/src/intel.h[m
[1m+++ b/src/intel.h[m
[36m@@ -24,6 +24,6 @@[m [mpublic:[m
 private:[m
     Geometry ssl_geometry_;[m
     State state_;[m
[31m-    std::vector<Robot> our_robots_;[m
[31m-    std::vector<Robot> their_robots_;[m
[32m+[m[32m    std::vector<Robot>* our_robots_;[m
[32m+[m[32m    std::vector<Robot>* their_robots_;[m
 };[m
