#include "main.h"
//global variables
extern MotorGroup leftSide ({Motor(2, false, AbstractMotor::gearset::green), Motor(3, false, AbstractMotor::gearset::green)});
extern MotorGroup rightSide ({Motor(4, true, AbstractMotor::gearset::green), Motor(5, true, AbstractMotor::gearset::green)});
extern Motor intake (6, false, AbstractMotor::gearset::green);
extern Motor launcher (7, false, AbstractMotor::gearset::red);
extern Motor lift (8, true, AbstractMotor::gearset::red);
extern Motor liftTilt (9, false, AbstractMotor::gearset::red);
extern ChassisControllerIntegrated chassis = ChassisControllerFactory::create(leftSide, rightSide, AbstractMotor::gearset::green, {4_in, 15_in});
bool initCompleted = false;

string status = "Disabled";

void init () {
  if (!initCompleted) {
    launcher.moveRelative(800, 100);
    lift.setBrakeMode(AbstractMotor::brakeMode::hold);
    liftTilt.setBrakeMode(AbstractMotor::brakeMode::hold);
    launcher.setBrakeMode(AbstractMotor::brakeMode::hold);
    initCompleted = true;
  }
}

void initialize () {}

// currnetly not using these functions
void disabled () {}

void competition_initialize () {}
