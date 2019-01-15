#include "main.h"
extern MotorGroup leftSide;
extern MotorGroup rightSide;
extern ChassisControllerIntegrated chassis;
extern bool autonEnabled;
extern lv_obj_t * autonEnable;

void autonomous() {
  lv_btn_set_state(autonEnable, LV_BTN_STATE_INA);
  if (autonEnabled) {
    chassis.moveDistance(1500);
    pros::Task::delay(250);
    chassis.moveDistance(-1990);
    pros::Task::delay(1000);
    chassis.turnAngle(290);
    chassis.moveDistance(1500);
  }
}
