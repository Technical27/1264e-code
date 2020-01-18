/*
  Contains source code for driver control which handles controller input

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

void trayControl (void*) {
  bool on = false;
  int time = pros::millis();
  int ptime = pros::millis();
  bool cooldownPassed;
  while (true) {
    cooldownPassed = time - ptime > 500;
    if (cooldownPassed && mainController.getDigital(ControllerDigital::B)) {
      ptime = pros::millis();
      tray.moveRelative(on ? 740 : -740, 600);
      on = !on;
    }
    time = pros::millis();
    pros::Task::delay(50);
  }
}

void liftControl (void*) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::R2)) {
      lift.move(127);
    }
    else if (mainController.getDigital(ControllerDigital::R1)) {
      lift.move(-127);
    }
    else {
      lift.move(0);
    }
    pros::Task::delay(50);
  }
}

void liftArmControl (void*) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::L2)) {
      liftLeft.move(127);
      liftRight.move(127);
    }
    else if (mainController.getDigital(ControllerDigital::L1)) {
      liftLeft.move(-127);
      liftRight.move(-127);
    }
    else {
      liftLeft.move(0);
      liftRight.move(0);
    }
    pros::Task::delay(50);
  }
}

// Controls motors by joysticks
void opcontrol () {
  mode = 2;
  debugLog("Starting Driver Control\n");
  loadObama();
  pros::Task trayTask (trayControl, nullptr, "tray");
  pros::Task liftTask (liftControl, nullptr, "lift");
  pros::Task liftArmTask (liftArmControl, nullptr, "liftArm");
  motorMutex.give();
  while (true) {
    if (motorMutex.take(0)) {
      motorMutex.take(5);
      chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY));
      motorMutex.give();
    }
    pros::Task::delay(10);
  }
}
