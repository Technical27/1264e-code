#include "include.hpp"

void autonomous () {
  for (int i = 0; i < loadedAuton.size(); i++) {
    frontRight.moveVelocity(loadedAuton[i][1]);
    frontLeft.moveVelocity(loadedAuton[i][2]);
    backRight.moveVelocity(loadedAuton[i][3]);
    backLeft.moveVelocity(loadedAuton[i][4]);
    pros::Task::delay(250);
  }
}