/*
  Contains all global variable definitions and init functions

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

// Variable definitions
Motor frontLeft (1, true, AbstractMotor::gearset::green);
Motor frontRight (2, false, AbstractMotor::gearset::green);
Motor backLeft (3, true, AbstractMotor::gearset::green);
Motor backRight (4, false, AbstractMotor::gearset::green);

Motor tray (5, false, AbstractMotor::gearset::red);
AsyncPosIntegratedController trayController = AsyncControllerFactory::posIntegrated(tray);

Motor lift (6, true, AbstractMotor::gearset::red);
AsyncPosIntegratedController liftController = AsyncControllerFactory::posIntegrated(lift);

Motor liftLeft(7, false, AbstractMotor::gearset::green);
Motor liftRight(8, true, AbstractMotor::gearset::green);

MotorGroup left ({frontLeft, backLeft});
MotorGroup right ({frontRight, backRight});

ChassisControllerIntegrated chassis = ChassisControllerFactory::create(left, right, AbstractMotor::gearset::green);

Controller mainController (ControllerId::master);

int mode = 0;

pros::Mutex motorMutex;

void initialize () {
  pros::Task screenTask (screenControl, nullptr, "screen");
  tray.setBrakeMode(AbstractMotor::brakeMode::hold);
  lift.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void disabled () {
  debugLog("Robot Disabled\n");
  loadMain();
}

void competition_initialize () {}
