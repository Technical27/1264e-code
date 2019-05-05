#include "include.hpp"

// Controls left and right movement by buttons, and also compensates for motor speed differences
void strafeControl (void* param) {
  double FLError = 0, FRError = 0, BLError = 0, BRError = 0;
  double Kp = 2;
  bool controllerLeft, controllerRight;
  int target = 190;
  int startVoltage = 11000;
  int reverse;

  while (true) {
    pros::Task::delay(25);
    controllerLeft = mainController.getDigital(ControllerDigital::left);
    controllerRight = mainController.getDigital(ControllerDigital::right);
    if (controllerLeft || controllerRight) {
      motorMutex.take(50);
      while (controllerLeft || controllerRight) {
        reverse = controllerLeft ? -1 : 1;
        frontLeft.moveVoltage(-reverse * startVoltage + (FLError * Kp));
        frontRight.moveVoltage(reverse * startVoltage + (FRError * Kp));
        backLeft.moveVoltage(reverse * startVoltage + (BLError * Kp));
        backRight.moveVoltage(-reverse * startVoltage + (BRError * Kp));
        
        FLError = target - frontLeft.getActualVelocity();
        FRError = target - frontRight.getActualVelocity();
        BLError = target - backLeft.getActualVelocity();
        BRError = target - backRight.getActualVelocity();
        
        controllerLeft = mainController.getDigital(ControllerDigital::left);
        controllerRight = mainController.getDigital(ControllerDigital::right);
        pros::Task::delay(25);
      }
      motorMutex.give();
    }
  }
}