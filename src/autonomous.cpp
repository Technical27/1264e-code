#include "main.h"
//global variables
extern Motor intake;
extern Motor puncher;
extern ChassisControllerIntegrated chassis;

void autonomous() {
  intake.moveVoltage(-12000);
  pros::Task::delay(5000);

  intake.moveVoltage(0);
  puncher.moveRelative(1800, 100);
  pros::Task::delay(1000);

  chassis.moveDistance(1500);
  chassis.moveDistance(-1400);
  chassis.turnAngle(90_deg);
  chassis.moveDistance(-350);

  intake.moveVoltage(-12000);
  chassis.setMaxVoltage(3000);
  chassis.moveDistance(1600);
  intake.moveVoltage(0);

  chassis.moveDistance(-400);
  intake.moveVoltage(12000);
  chassis.moveDistance(400);
  intake.moveVoltage(0);

  chassis.turnAngle(-90_deg);
  chassis.setMaxVoltage(12000);
  intake.moveVoltage(-12000);
  pros::Task::delay(2000);
  intake.moveVoltage(0);
  puncher.moveRelative(1800, 100);
  pros::Task::delay(1000);
  chassis.moveDistance(1500);
}
