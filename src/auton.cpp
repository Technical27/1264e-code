/*
  Contains source code for autonomous

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

void autonomous () {
  if (autonLoaded && size != 0) {
    for (int i = 0; i < size; i++) {
      frontRight.moveVelocity(loadedAuton[i][0]);
      frontLeft.moveVelocity(loadedAuton[i][1]);
      backRight.moveVelocity(loadedAuton[i][2]);
      backLeft.moveVelocity(loadedAuton[i][3]);
      pros::Task::delay(20);
    }
  }
}
