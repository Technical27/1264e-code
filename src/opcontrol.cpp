#include "main.h"
//importing/creating all variables
extern MotorGroup leftSide;
extern MotorGroup rightSide;
extern Motor intake;
extern ChassisControllerIntegrated chassis;
Controller mainController (ControllerId::master);
Controller auxController (ControllerId::partner);

void intakeControl (void * param) {
  //loop to control intake motor
  while (true) {
    if (mainController.getDigital(ControllerDigital::R1)) intake.moveVoltage(12000);
    else if (mainController.getDigital(ControllerDigital::R2)) intake.moveVoltage(-12000);
    else intake.moveVoltage(0);
    pros::Task::delay(10);
  }
}

void liftControl (void * param) {

}

void opcontrol() {
  //tasks to control other functions
  pros::Task intakeTask (intakeControl);
  pros::Task liftTask (liftControl);
  //loop to control the drive train
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY), 0.2);
    pros::Task::delay(10);
  }
}
