#include "main.h"
//global variables
MotorGroup leftSide ({Motor(2, false, AbstractMotor::gearset::green), Motor(3, false, AbstractMotor::gearset::green)});
MotorGroup rightSide ({Motor(4, true, AbstractMotor::gearset::green), Motor(5, true, AbstractMotor::gearset::green)});
extern Motor intake (6, false, AbstractMotor::gearset::green);
extern Motor puncher (7, false, AbstractMotor::gearset::red);
extern ChassisControllerIntegrated chassis = ChassisControllerFactory::create(leftSide, rightSide, AbstractMotor::gearset::green, {4_in, 15_in});

void initialize () {
  puncher.moveRelative(800, 100);
  puncher.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// currnetly not using these functions
void disabled () {}

void competition_initialize () {}
