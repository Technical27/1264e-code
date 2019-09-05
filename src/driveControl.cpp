#include "include.hpp"

void clawControl (void*) {
  bool on = false;
  int time = pros::millis();
  int ptime = pros::millis();
  bool cooldownPassed;
  while (true) {
    cooldownPassed = time - ptime > 500;
    if (mainController.getDigital(ControllerDigital::A) && cooldownPassed && !on) {
      ptime = pros::millis();
      on = true;
      claw.moveRelative(500, 3000);
    }
    else if (mainController.getDigital(ControllerDigital::B) && cooldownPassed && on) {
      ptime = pros::millis();
      on = false;
      claw.moveRelative(500, 3000);
    }
    time = pros::millis();
    pros::Task::delay(10);
  }
}

// Controls motors by joysticks
void opcontrol () {
  pros::Task clawTask (clawControl);
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY));
    pros::Task::delay(10);
  }
}
