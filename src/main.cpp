#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>

#include "robot.h"
#include "intel.h"

#include "env/utils.h"
#include "env/ssl_geometry.h"
#include "env/state.h"
#include "env/ball.h"

#include "ctrl/command.h"
#include "ctrl/pid.h"

using namespace std;

// Checks version of protocol
bool VERSION_CHECK(){
  const int compat_version = 1;
  string magic_string;
  int version;
  cin >> magic_string >> version;
  if (magic_string == "ROBOIME_AI_PROTOCOL" && version == compat_version) {
    cout << "COMPATIBLE " << compat_version << endl;
    return true;
  } else {
    cout << "NOT_COMPATIBLE " << compat_version << endl;
    return false;
  }
}

int main(int argc, char **argv) {
  bool test_goalie = false;
  bool test_attacker = false;
  if (argc > 1) {
    if (strcmp(argv[1], "-g") == 0) {
      test_goalie = true;
    } else if (strcmp(argv[1], "-a") == 0) {
      test_attacker = true;
    } else {
      cerr << "Unrecognized flag: " << argv[1] << endl;
      return 1;
    }
  } else if (argc > 2) {
      cerr << "Too many flags" << endl;
      return 1;
  }
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  cerr.sync_with_stdio(false);
  cerr << "started" << endl;
  // Version check I/O
  assert(VERSION_CHECK());
  cerr << "compatible" << endl;
  Intel intel;
  intel.setTestGoalie(test_goalie);
  intel.setTestAttacker(test_attacker);
  // Geometry input
  intel.geometryInput();
  // Game state I/O
  intel.loop();
}

