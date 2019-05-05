#include "include.hpp"

Motor frontLeft (4, false, AbstractMotor::gearset::green);
Motor frontRight (14, true, AbstractMotor::gearset::green);
Motor backLeft (15, false, AbstractMotor::gearset::green);
Motor backRight (5, true, AbstractMotor::gearset::green);

MotorGroup left ({frontLeft, backLeft});
MotorGroup right ({frontRight, backRight});

Controller mainController (ControllerId::master);

pros::Mutex motorMutex;

void screenControl (void* param) {
  while (true) pros::Task::delay(100);
}

void initialize () {
  pros::Task screenTask (screenControl);
}

void disabled () {}

void competition_initialize () {}