#include "include.hpp"

void autonomous () {
  for (int i = 0; i < loadedAuton.size(); i++) {
    frontRight.moveVelocity(loadedAuton[i][0]);
    frontLeft.moveVelocity(loadedAuton[i][1]);
    backRight.moveVelocity(loadedAuton[i][2]);
    backLeft.moveVelocity(loadedAuton[i][3]);
    pros::Task::delay(20);
  }
}