#include "include.hpp"

void clawControl (void*) {
  bool rOn = false;
  bool eOn = false;
  int rtime = pros::millis();
  int rptime = pros::millis();
  int etime = pros::millis();
  int eptime = pros::millis();
  while (true) {
    if (mainController.getDigital(ControllerDigital::A) && rtime - rptime > 500) {
      rptime = pros::millis();
      rOn = !rOn;
      if (rOn) claw.moveRelative(500, 3000);
    }
    else if (mainController.getDigital(ControllerDigital::B) && etime - eptime > 500) {
      eptime = pros::millis();
      eOn = !eOn;
      if (eOn) claw.moveRelative(500, 3000);
    }
    etime = pros::millis();
    rtime = pros::millis();
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
