#include "include.hpp"

void clawControl (void*) {
  bool on = false;
  int time = pros::millis();
  int ptime = pros::millis();
  while (true) {
    if (mainController.getDigital(ControllerDigital::A) && time - ptime > 500) {
      ptime = pros::millis();
      on = !on;
      on ? claw.moveRelative(150, 3000) : claw.moveRelative(-150, 3000);
    }
    time = pros::millis();
    pros::Task::delay(10);
  }
}

// Controls motors by joysticks
void opcontrol () {
  pros::Task buttons (clawControl);
  while (true) {
    left.moveVoltage(mainController.getAnalog(ControllerAnalog::leftY) * 12000);
    right.moveVoltage(mainController.getAnalog(ControllerAnalog::rightY) * 12000);
    pros::Task::delay(10);
  }
}