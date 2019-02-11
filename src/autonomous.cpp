#include "main.h"
//global variables
extern Motor intake;
extern Motor launcher;
extern ChassisControllerIntegrated chassis;
extern bool autonEnabled;
extern lv_obj_t * tabs;
extern lv_obj_t * autonEnable;
extern lv_obj_t * allianceSelectList;
extern lv_obj_t * sideSelectList;
extern lv_obj_t * autonSelectList;

void autonomous() {
  //disables the auton enable button
  lv_btn_set_state(autonEnable, LV_BTN_STATE_INA);
  //changes to the telemetry in the tabview
  lv_tabview_set_tab_act(tabs, 1, true);
  if (autonEnabled) {
    //gets the selected item from the lists
    int program = lv_ddlist_get_selected(autonSelectList);
    int alliance = lv_ddlist_get_selected(allianceSelectList);
    int side = lv_ddlist_get_selected(sideSelectList);

    //uses conditions to check for side, alliance, and if it is normal or skills
    if (program == 0) {
      if (side == 0) {
        launcher.moveRelative(1800, 100);
        chassis.moveDistance(1500);// Go to flag and back
        pros::Task::delay(250);
        chassis.moveDistance(-1990);
        pros::Task::delay(1000);

        if (alliance == 0) chassis.turnAngle(90_deg);// Turn to the platform
        else if (alliance == 1) chassis.turnAngle(-90_deg);

        chassis.moveDistance(-125);// Drive to the platform
        chassis.moveDistance(1700);
      }
      else if (side == 1) {
        intake.moveVoltage(12000);
        chassis.moveDistance(500);
        intake.moveVoltage(0);
        chassis.moveDistance(-600);
      }
    }
    else if (program == 1) {
      launcher.moveRelative(1800, 100);
      chassis.moveDistance(1500);// Go to flag and back
      pros::Task::delay(250);
      chassis.moveDistance(-1990);
      pros::Task::delay(1000);

      chassis.turnAngle(90_deg);// Turn to the platform

      chassis.moveDistance(-125);// Drive to the platform
      chassis.moveDistance(2500);
      //WIP skills auton
      /*chassis.moveDistance(1500);
      pros::Task::delay(250);// Go and hit first flag and go back a bit
      chassis.moveDistance(-500);
      pros::Task::delay(250);

      chassis.turnAngle(290);
      intake.moveVoltage(12000);// Go to the next flag and flip the cap on the way
      chassis.moveDistance(1300);
      intake.moveVoltage(0);
      pros::Task::delay(250);

      chassis.turnAngle(-290);
      chassis.moveDistance(500);
      pros::Task::delay(250);// Turn and go to hit the flag and then comes back
      chassis.moveDistance(-500);

      pros::Task::delay(250);
      chassis.turnAngle(290);// Goes to the next flag and hits the cap
      intake.moveVoltage(12000);
      chassis.moveDistance(1300);
      pros::Task::delay(250);
      chassis.turnAngle(-290);

      intake.moveVoltage(0);
      pros::Task::delay(250);
      chassis.moveDistance(500);
      pros::Task::delay(250);// Goes to the flag and then comes back
      chassis.moveDistance(-500);
      chassis.turnAngle(-290);
      chassis.moveDistance(-700);
      chassis.turnAngle(290);
      chassis.moveDistance(-1350);

      pros::Task::delay(1000);
      chassis.turnAngle(-290);// Turn and go to the center platform
      chassis.moveDistance(-125);
      chassis.moveDistance(2500);*/
    }
  }
}
