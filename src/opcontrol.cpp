#include "include.hpp"
Controller mainController (ControllerId::master);

void driveControl (void* param) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::left)) {
      frontLeft.move(-127);
      backRight.move(-127);
      frontRight.move(127);
      backLeft.move(127);
    }
    else if (mainController.getDigital(ControllerDigital::right)) {
      frontLeft.move(127);
      backRight.move(127);
      frontRight.move(-127);
      backLeft.move(-127);
    }
    else {
      int left = mainController.getAnalog(ControllerAnalog::leftY) * 127;
      int right = mainController.getAnalog(ControllerAnalog::rightY) * 127;
      frontLeft.move(left);
      backLeft.move(left);
      frontRight.move(right);
      backRight.move(right);
    }
    pros::Task::delay(10);
  }
}

void opcontrol () {
  pros::Task driveTask (driveControl);
  while (true) pros::Task::delay(10);
}
