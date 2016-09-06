#include <iostream>
#include <vector>
#include <assert.h>

#include "robot.h"
#include "intel.h"

#include "env/utils.h"
#include "env/ssl_geometry.h"
#include "env/state.h"
#include "env/ball.h"

#include "ctrl/command.h"
#include "ctrl/pid.h"

using namespace std;
using namespace util;

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

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cerr.sync_with_stdio(false);
    cerr << "started" << endl;
    // Version check I/O
    assert(VERSION_CHECK());
    cerr << "compatible" << endl;
    Intel intel;
    // Geometry input
    intel.geometryInput();
    // Game state I/O
    intel.loop();
}

