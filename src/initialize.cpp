#include "main.h"
MotorGroup leftSide ({Motor(2, false, AbstractMotor::gearset::green), Motor(3, false, AbstractMotor::gearset::green)});
MotorGroup rightSide ({Motor(4, true, AbstractMotor::gearset::green), Motor(5, true, AbstractMotor::gearset::green)});
extern ChassisControllerIntegrated chassis = ChassisControllerFactory::create(leftSide, rightSide, AbstractMotor::gearset::green, {4_in, 15_in});

void initialize () {}

void disabled () {}

void competition_initialize () {}