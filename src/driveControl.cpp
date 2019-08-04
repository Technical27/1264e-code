#include "include.hpp"

// Controls motors by joysticks
void opcontrol () {
  while (true) {
    left.moveVoltage(mainController.getAnalog(ControllerAnalog::leftY) * 12000);
    right.moveVoltage(mainController.getAnalog(ControllerAnalog::rightY) * 12000);
    pros::Task::delay(10);
  }
}