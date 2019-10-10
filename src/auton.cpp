/*
  Contains source code for autonomous

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

void autonomous () {
  // Skills
  if (currentAuton == 3) {
    debugLog("Starting skills auton");
  }
  // Blue and red autons
  else if (currentAuton != 0) {
    debugLog("Starting Normal auton");
  }
}
