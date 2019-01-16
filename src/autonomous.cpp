#include "main.h"
extern MotorGroup leftSide;
extern MotorGroup rightSide;
extern ChassisControllerIntegrated chassis;
extern bool autonEnabled;
extern lv_obj_t * autonEnable;
extern lv_obj_t * sideSelectList;
extern lv_obj_t * allianceSelectList;
extern lv_obj_t * autonSelectList;

void autonomous() {
  lv_btn_set_state(autonEnable, LV_BTN_STATE_INA);
  int program = lv_ddlist_get_selected(autonSelectList);
  if (autonEnabled) {
    if (program == 0) {
      int alliance = lv_ddlist_get_selected(allianceSelectList);
      int side = lv_ddlist_get_selected(sideSelectList);
      if (side == 0) {
        chassis.moveDistance(1500);
        pros::Task::delay(250);
        chassis.moveDistance(-1990);
        pros::Task::delay(1000);
        if (alliance == 0) chassis.turnAngle(290);
        else if (alliance == 1) chassis.turnAngle(-290);
        chassis.moveDistance(-125);
        chassis.moveDistance(1700);
      }
      else if (side == 1) {}
    }
    else if (program == 1) {

    }
  }
}
