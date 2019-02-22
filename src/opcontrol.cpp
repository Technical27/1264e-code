#include "main.h"
//global variables
extern Motor intake;
extern Motor launcher;
extern ChassisControllerIntegrated chassis;
Controller mainController (ControllerId::master);
Controller auxController (ControllerId::partner);
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

void launcherControl (void * param) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::L2)) launcher.moveRelative(1800, 100);
    else if (mainController.getDigital(ControllerDigital::A) && intakeMutex.take(0)) {
      intakeMutex.take(500);
      intake.moveVoltage(-12000);
      launcher.moveRelative(1800, 100);
      pros::Task::delay(600);
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
  //tasks to control other functions
  pros::Task intakeTask (intakeControl);
  pros::Task launcherTask (launcherControl);
  pros::Task driveTask (driveControl);
  //loop to control the drive train
  while (true) pros::Task::delay(10);
}
