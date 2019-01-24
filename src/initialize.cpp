#include "main.h"
extern MotorGroup leftSide ({Motor(2, false, AbstractMotor::gearset::green), Motor(3, false, AbstractMotor::gearset::green)});
extern MotorGroup rightSide ({Motor(4, true, AbstractMotor::gearset::green), Motor(5, true, AbstractMotor::gearset::green)});
extern Motor intake (6, false, AbstractMotor::gearset::green);
extern ChassisControllerIntegrated chassis = ChassisControllerFactory::create(leftSide, rightSide, AbstractMotor::gearset::green);
extern bool autonEnabled = true;
lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * autonTab = lv_tabview_add_tab(tabs, "Auton");
lv_obj_t * telemetryTab = lv_tabview_add_tab(tabs, "Telemetry");
lv_obj_t * autonEnableLabel = lv_label_create(autonTab, NULL);
extern lv_obj_t * autonEnable = lv_btn_create(autonTab, NULL);
lv_obj_t * competitionStatus = lv_label_create(telemetryTab, NULL);
extern lv_obj_t * allianceSelectList = lv_ddlist_create(autonTab, NULL);
extern lv_obj_t * sideSelectList = lv_ddlist_create(autonTab, NULL);
extern lv_obj_t * autonSelectList = lv_ddlist_create(autonTab, NULL);
string status = "Disabled";

lv_res_t autonEnabler (lv_obj_t * btn) {
  autonEnabled = !autonEnabled;
  if (autonEnabled) lv_label_set_text(autonEnableLabel, "Auton Enabled " SYMBOL_OK);
  else lv_label_set_text(autonEnableLabel, "Auton Disabled " SYMBOL_CLOSE);
  return LV_RES_OK;
}

void screenController (void * param) {
  lv_ddlist_set_options(allianceSelectList, "Red\nBlue");//Setup for display elements
  lv_ddlist_set_options(sideSelectList, "Front\nBack");
  lv_ddlist_set_options(autonSelectList, "Normal\nSkills");
  lv_obj_set_size(autonEnable, 175, 50);
  lv_obj_align(allianceSelectList, autonTab, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
  lv_obj_align(autonSelectList, autonTab, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_obj_align(sideSelectList, autonTab, LV_ALIGN_IN_TOP_LEFT, 15, 0);
  lv_obj_align(autonEnable, autonTab, LV_ALIGN_IN_BOTTOM_MID, 0, 10);
  lv_label_set_text(autonEnableLabel, "Auton Enabled " SYMBOL_OK);
  lv_btn_set_action(autonEnable, LV_BTN_ACTION_CLICK, autonEnabler);
  lv_obj_align(autonEnableLabel, autonEnable, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(competitionStatus, telemetryTab, LV_ALIGN_CENTER, 0, 0);

  while (true) {
    if (pros::competition::is_disabled()) status = "Disabled";
    else if (pros::competition::is_autonomous()) status = "Autonomous";
    else status = "Driver Control";
    lv_label_set_text(competitionStatus, status.c_str());
    pros::Task::delay(100);
  }
}

void initialize () {
  pros::Task screenTask (screenController);
}

void disabled () {}

void competition_initialize () {}
