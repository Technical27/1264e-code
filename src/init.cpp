/*
  Contains all global variable definitions and init functions

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

// Variable definitions
Motor frontLeft (16, true, AbstractMotor::gearset::green);
Motor frontRight (8, false, AbstractMotor::gearset::green);
Motor backLeft (14, true, AbstractMotor::gearset::green);
Motor backRight (10, false, AbstractMotor::gearset::green);

Motor claw (1, true, AbstractMotor::gearset::green);

MotorGroup left ({frontLeft, backLeft});
MotorGroup right ({frontRight, backRight});

ChassisControllerIntegrated chassis = ChassisControllerFactory::create(left, right, AbstractMotor::gearset::green);

Controller mainController (ControllerId::master);

int mode = 0;

void initialize () {
  pros::Task screenTask (screenControl, nullptr, "screen");
  claw.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void disabled () {
  debugLog("Robot Disabled\n");
  loadMain();
}

void competition_initialize () {}
