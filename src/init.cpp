/*
  Contains all global variable definitions and init functions

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

// Variable definitions
Motor frontLeft (1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor frontRight (2, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor backLeft (3, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor backRight (4, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

Motor tray (5, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
std::shared_ptr<AsyncPositionController<double, double>> trayController = AsyncPosControllerBuilder().withMotor(tray).build();

Motor lift (6, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
std::shared_ptr<AsyncPositionController<double, double>> liftController = AsyncPosControllerBuilder().withMotor(lift).build();

Motor liftLeft(7, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor liftRight(8, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

MotorGroup left ({frontLeft, backLeft});
MotorGroup right ({frontRight, backRight});

std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder().withMotors(left, right).build();

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
