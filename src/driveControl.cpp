#include "include.hpp"

// Controls motors by joysticks
void driveControl (void*) {
  while (true) {
    pros::Task::delay(25);
    if (!motorMutex.take(0)) continue;
    motorMutex.take(5);
    left.moveVoltage(mainController.getAnalog(ControllerAnalog::leftY) * 12000);
    right.moveVoltage(mainController.getAnalog(ControllerAnalog::rightY) * 12000);
    motorMutex.give();
  }
}

void opcontrol () {
  pros::Task driveTask (driveControl);
  pros::Task strafeTask (strafeControl);
  while (true) pros::Task::delay(10);
}