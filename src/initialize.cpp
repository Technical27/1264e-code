#include "include.hpp"

Motor frontLeft (11, false, AbstractMotor::gearset::green);
Motor frontRight (1, true, AbstractMotor::gearset::green);
Motor backLeft (16, false, AbstractMotor::gearset::green);
Motor backRight (5, true, AbstractMotor::gearset::green);

void screenControl (void* param) {
  while (true) pros::Task::delay(100);
}

void initialize () {
  pros::Task screenTask (screenControl);
}

void disabled () {}

void competition_initialize () {}