#include "main.h"
extern Motor intake;
extern Motor puncher;
extern ChassisControllerIntegrated chassis;
Controller mainController (ControllerId::master);
Controller auxController (ControllerId::partner);
pros::Mutex intakeMutex;

void intakeControl (void * param) {
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

void puncherControl (void * param) {
  while (true) {
    if (mainController.getDigital(ControllerDigital::L2)) puncher.moveRelative(1800, 100);
    else if (mainController.getDigital(ControllerDigital::A) && intakeMutex.take(0)) {
      intakeMutex.take(500);
      intake.moveVoltage(-12000);
      puncher.moveRelative(1800, 100);
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
  pros::Task intakeTask (intakeControl);
  pros::Task puncherTask (puncherControl);
  pros::Task driveTask (driveControl);
  while (true) pros::Task::delay(10);
}
