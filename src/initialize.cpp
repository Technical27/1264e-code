#include "include.hpp"
ChassisControllerIntegrated chassis = ChassisControllerFactory::create({2, 3}, {-4, -5}, AbstractMotor::gearset::green);

void initialize () {}

void disabled () {}

void competition_initialize () {}