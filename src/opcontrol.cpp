#include "main.h"
extern MotorGroup leftSide;
extern MotorGroup rightSide;
extern Motor intake;
extern ChassisControllerIntegrated chassis;
Controller controller (ControllerId::master);

void intakeControl (void * param) {
  while (true) {
    if (controller.getDigital(ControllerDigital::R1)) intake.moveVoltage(12000);
    else if (controller.getDigital(ControllerDigital::R2)) intake.moveVoltage(-12000);
    else intake.moveVoltage(0);
    pros::Task::delay(10);
  }
}

void opcontrol() {
  pros::Task intakeTask (intakeControl);
  while (true) {
    chassis.tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY), 0.2);
    pros::Task::delay(10);
  }
}
