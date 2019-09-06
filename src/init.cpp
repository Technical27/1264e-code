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

ADIButton menuLeft (2);
ADIButton menuRight (3);

ADIGyro mainGyro (4);

std::vector<std::unique_ptr<double[]>> loadedAuton;

bool autonLoaded = false;

void initialize () {
  pros::Task screenTask (screenControl, nullptr, "screen");
  autonLoaded = loadAuton("/usd/auton");
  claw.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// Unused functions
void disabled () {}

void competition_initialize () {}
