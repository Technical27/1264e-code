/*
  Contains source code for driver control which handles controller input

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

void clawControl (void*) {
  bool on = false;
  int time = pros::millis();
  int ptime = pros::millis();
  bool cooldownPassed;
  while (true) {
    cooldownPassed = time - ptime > 500;
    if (mainController.getDigital(ControllerDigital::A) && cooldownPassed && !on) {
      ptime = pros::millis();
      on = true;
      claw.moveRelative(1550, 600);
    }
    else if (mainController.getDigital(ControllerDigital::B) && cooldownPassed && on) {
      ptime = pros::millis();
      on = false;
      claw.moveRelative(-1550, 600);
    }
    time = pros::millis();
    pros::Task::delay(10);
  }
}

// Controls motors by joysticks
void opcontrol () {
  debugLog("Starting Driver Control\n");
  pros::Task clawTask (clawControl, nullptr, "claw");
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY));
    pros::Task::delay(10);
  }
}
