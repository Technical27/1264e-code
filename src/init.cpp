/*
  Contains all global variable definitions and init functions

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

// Variable definitions
Motor frontLeft (10, false, AbstractMotor::gearset::green);
Motor frontRight (20, true, AbstractMotor::gearset::green);
Motor backLeft (1, false, AbstractMotor::gearset::green);
Motor backRight (11, true, AbstractMotor::gearset::green);

Motor claw (21);

MotorGroup left ({frontLeft, backLeft});
MotorGroup right ({frontRight, backRight});

ChassisControllerIntegrated chassis = ChassisControllerFactory::create(left, right, AbstractMotor::gearset::green);

Controller mainController (ControllerId::master);

void initialize () {
  pros::Task screenTask (screenControl, nullptr, "screen");
  claw.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// Unused functions
void disabled () {
  if (errorArea != nullptr) debugLog("Robot Disabled");
}

void competition_initialize () {}
