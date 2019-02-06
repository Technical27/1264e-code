#include "main.h"
//importing/creating all variables
extern MotorGroup leftSide;
extern MotorGroup rightSide;
extern Motor intake;
extern ChassisControllerIntegrated chassis;
Controller controller (ControllerId::master);

void intakeControl (void * param) {
  //loop to control intake motor
  while (true) {
    if (controller.getDigital(ControllerDigital::R1)) intake.moveVoltage(12000);
    else if (controller.getDigital(ControllerDigital::R2)) intake.moveVoltage(-12000);
    else intake.moveVoltage(0);
    pros::Task::delay(10);
  }
}

void opcontrol() {
  pros::Task intakeTask (intakeControl);
  //loop to control the drive train
  while (true) {
    chassis.tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY), 0.2);
    pros::Task::delay(10);
  }
}
