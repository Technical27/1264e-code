#include "main.h"
//global variables
extern Motor intake;
extern Motor launcher;
extern ChassisControllerIntegrated chassis;

void autonomous() {
  init();
  intake.moveVoltage(-12000);
  pros::Task::delay(5000);
  intake.moveVoltage(0);
  launcher.moveRelative(1800, 100);
  pros::Task::delay(1000);
  chassis.moveDistance(1500);
  chassis.moveDistance(-1990);
  chassis.turnAngle(90_deg);
  chassis.moveDistance(-350);
  chassis.moveDistance(3900);
}
