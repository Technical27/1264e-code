#include "main.h"
//global variables
extern Motor intake;
extern Motor launcher;
extern Motor lift;
extern Motor liftTilt;
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
  while (true) {
    if (auxController.getDigital(ControllerDigital::L1)) lift.moveVoltage(12000);
    else if (auxController.getDigital(ControllerDigital::L2)) lift.moveVoltage(-12000);
    else lift.moveVoltage(0);

    if (auxController.getDigital(ControllerDigital::R1) && liftTilt.getTargetPosition() == 0) liftTilt.moveRelative(255, 100);
    else if (auxController.getDigital(ControllerDigital::R2) && liftTilt.getTargetPosition() == 0) liftTilt.moveRelative(-225, 100);
  }
}

void launcherControl (void * param) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::L2) && launcher.getTargetPosition() == 0) launcher.moveRelative(300, 100);
  }
}

void opcontrol() {
  //tasks to control other functions
  pros::Task intakeTask (intakeControl);
  pros::Task liftTask (liftControl);
  pros::Task launcherTask (launcherControl);
  //loop to control the drive train
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY), 0.2);
    pros::Task::delay(10);
  }
}
