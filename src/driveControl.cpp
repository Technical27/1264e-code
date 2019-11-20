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
    if (mainController.getDigital(ControllerDigital::R2) && cooldownPassed && !on) {
      ptime = pros::millis();
      on = true;
      claw.moveRelative(740, 600);
    }
    else if (mainController.getDigital(ControllerDigital::R1) && cooldownPassed && on) {
      ptime = pros::millis();
      on = false;
      claw.moveRelative(-740, 600);
    }
    time = pros::millis();
    pros::Task::delay(10);
  }
}

// Controls motors by joysticks
void opcontrol () {
  mode = 2;
  debugLog("Starting Driver Control\n");
  loadObama();
  pros::Task clawTask (clawControl, nullptr, "claw");
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY) * 0.75, mainController.getAnalog(ControllerAnalog::rightY) * 0.75);
    pros::Task::delay(10);
  }
}
