#include "include.hpp"
Controller mainController (ControllerId::master);

void driveControl (void * param) {
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY), 0.2);
    pros::Task::delay(10);
  }
}

void opcontrol () {
  pros::Task driveTask (driveControl);
  while (true) pros::Task::delay(10);
}
