#include "main.h"
//global variables
extern Motor intake;
extern Motor launcher;
extern Motor lift;
extern Motor liftTilt;
extern ChassisControllerIntegrated chassis;
Controller mainController (ControllerId::master);
Controller auxController (ControllerId::partner);
bool reversed = false;
bool rev = false;
pros::Mutex intakeMutex;

void intakeControl (void * param) {
  //loop to control intake motor
  while (true) {
    if (intakeMutex.take(0)) {
      intakeMutex.take(100);
      if (mainController.getDigital(ControllerDigital::R1)) intake.moveVoltage(12000);
      else if (mainController.getDigital(ControllerDigital::R2)) intake.moveVoltage(-12000);
      else intake.moveVoltage(0);
      intakeMutex.give();
    }
    pros::Task::delay(10);
  }
}

void liftControl (void * param) {
  while (true) {
    if (auxController.getDigital(ControllerDigital::L1)) lift.moveVoltage(12000);
    else if (auxController.getDigital(ControllerDigital::L2)) lift.moveVoltage(-12000);
    else lift.moveVoltage(0);

    if (auxController.getDigital(ControllerDigital::R1)) liftTilt.moveVoltage(6000);
    else if (auxController.getDigital(ControllerDigital::R2)) liftTilt.moveVoltage(-6000);
    else liftTilt.moveVoltage(0);
  }
}

void launcherControl (void * param) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::L2)) launcher.moveRelative(1800, 100);
    if (mainController.getDigital(ControllerDigital::A) && intakeMutex.take(0)) {
      intakeMutex.take(500);
      intake.moveVoltage(-12000);
      launcher.moveRelative(1800, 100);
      pros::Task::delay(100);
      pros::Task::delay(500);
      intakeMutex.give();
    }
  }
}

void driveControl (void * param) {
  while (true) {
    chassis.tank(mainController.getAnalog(ControllerAnalog::leftY), mainController.getAnalog(ControllerAnalog::rightY), 0.2);
    pros::Task::delay(10);
  }
}

void opcontrol() {
  init();
  //tasks to control other functions
  pros::Task intakeTask (intakeControl);
  pros::Task liftTask (liftControl);
  pros::Task launcherTask (launcherControl);
  pros::Task driveTask (driveControl);
  //loop to control the drive train
  while (true) pros::Task::delay(10);
}
