#include "include.hpp"

// Variable definitions
Motor frontLeft (4, false, AbstractMotor::gearset::green);
Motor frontRight (14, true, AbstractMotor::gearset::green);
Motor backLeft (15, false, AbstractMotor::gearset::green);
Motor backRight (5, true, AbstractMotor::gearset::green);

MotorGroup left ({frontLeft, backLeft});
MotorGroup right ({frontRight, backRight});

Controller mainController (ControllerId::master);

ADIButton menuLeft (2);
ADIButton menuRight (3);

ADIGyro mainGyro (4);

pros::Mutex motorMutex;

std::vector<std::unique_ptr<double[]>> loadedAuton;

void initialize () {
  pros::Task screenTask (screenControl);
}

// Unused functions
void disabled () {}

void competition_initialize () {}