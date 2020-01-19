/*
  Contains source code for autonomous

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

void auton (void*) {
  mode = 1;
  loadObama();
  motorMutex.take(20);
  // red auton
  if (autonMode == 1) {
    debugLog("Starting red auton\n");
    if (currentAuton == 1) {
      chassis->moveRaw(700);
      chassis->moveRaw(-700);
    }
  }
  // blue auton
  else if (autonMode == 2) {
    debugLog("Starting blue auton\n");
  }
  // skills
  else if (autonMode == 3) {
    debugLog("Starting skills auton\n");
  }
  motorMutex.give();
}

void autonomous () {auton(nullptr);}
