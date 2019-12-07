/*
  Contains source code for autonomous

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

void openClaw() {
  claw.moveRelative(740, 600);
  pros::Task::delay(10);
  while(!claw.isStopped()) pros::Task::delay(10);
}

void closeClaw() {
  claw.moveRelative(-740, 600);
  pros::Task::delay(10);
  while (!claw.isStopped()) pros::Task::delay(10);
}

void auton (void*) {
  mode = 1;
  loadObama();
  motorMutex.take(20);
  // red auton
  if (autonMode == 1) {
    debugLog("Starting red auton\n");
    if (currentAuton == 1) {
      chassis.moveDistance(700);
      chassis.moveDistance(-700);
      claw.moveRelative(1480, 600);
    }
    else if (currentAuton == 2) {
      /*chassis.moveDistance(700);
      claw.moveRelative(2140, 600);
      pros::Task::delay(10);
      while (!claw.isStopped()) pros::Task::delay(10);
      chassis.moveDistance(-700);
      chassis.turnAngle(-90);
      chassis.moveDistance(500);
      closeClaw();
      chassis.moveDistance(-500);
      chassis.turnAngle(90);
      chassis.moveDistance(800);
      openClaw();
      chassis.moveDistance(-800);
      chassis.turnAngle(-90);
      chassis.moveDistance(500);
      closeClaw();
      chassis.moveDistance(-500);
      chassis.turnAngle(90);*/
    }
  }
  // blue auton
  else if (autonMode == 2) {
    debugLog("Starting blue auton\n");
    claw.moveRelative(1480, 600);
  }
  // skills
  else if (autonMode == 3) {
    debugLog("Starting skills auton\n");
    claw.moveRelative(1480, 600);
  }
  else {
    claw.moveRelative(1480, 600);
  }
  motorMutex.give();
}

void autonomous () {auton(nullptr);}
