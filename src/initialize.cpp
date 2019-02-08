#include "main.h"
//global variables
extern MotorGroup leftSide ({Motor(2, false, AbstractMotor::gearset::green), Motor(3, false, AbstractMotor::gearset::green)});
extern MotorGroup rightSide ({Motor(4, true, AbstractMotor::gearset::green), Motor(5, true, AbstractMotor::gearset::green)});
extern Motor intake (6, false, AbstractMotor::gearset::green);
extern Motor launcher (7, false, AbstractMotor::gearset::red);
extern Motor lift (8, false, AbstractMotor::gearset::red);
extern Motor liftTilt (9, false, AbstractMotor::gearset::red);
extern ChassisControllerIntegrated chassis = ChassisControllerFactory::create(leftSide, rightSide, AbstractMotor::gearset::green, {4_in, 15_in});
extern bool autonEnabled = true;
extern lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
extern lv_obj_t * autonTab = lv_tabview_add_tab(tabs, "Auton");
extern lv_obj_t * telemetryTab = lv_tabview_add_tab(tabs, "Telemetry");
extern lv_obj_t * autonEnableLabel = lv_label_create(autonTab, NULL);
extern lv_obj_t * autonEnable = lv_btn_create(autonTab, NULL);
extern lv_obj_t * competitionStatus = lv_label_create(telemetryTab, NULL);
extern lv_obj_t * allianceSelectList = lv_ddlist_create(autonTab, NULL);
extern lv_obj_t * sideSelectList = lv_ddlist_create(autonTab, NULL);
extern lv_obj_t * autonSelectList = lv_ddlist_create(autonTab, NULL);

string status = "Disabled";

//function to handle the button pressing to enable and disable auton
lv_res_t autonEnabler (lv_obj_t * btn) {
  autonEnabled = !autonEnabled;
  if (autonEnabled) lv_label_set_text(autonEnableLabel, "Auton Enabled " SYMBOL_OK);
  else lv_label_set_text(autonEnableLabel, "Auton Disabled " SYMBOL_CLOSE);
  return LV_RES_OK;
}

void displayInit () {
  //Setup for display elements
  lv_ddlist_set_options(allianceSelectList, "Red\nBlue");
  lv_ddlist_set_options(sideSelectList, "Front\nBack");
  lv_ddlist_set_options(autonSelectList, "Normal\nSkills");

  lv_obj_set_size(autonEnable, 175, 50);
  lv_obj_set_pos(allianceSelectList, 50, 10);
  lv_obj_set_pos(autonSelectList, 200, 10);
  lv_obj_set_pos(sideSelectList, 350, 10);
  lv_obj_set_pos(autonEnable, 150, 100);

  lv_label_set_text(autonEnableLabel, "Auton Enabled " SYMBOL_OK);
  lv_btn_set_action(autonEnable, LV_BTN_ACTION_CLICK, autonEnabler);

  lv_obj_align(autonEnableLabel, autonEnable, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(competitionStatus, telemetryTab, LV_ALIGN_CENTER, 0, 0);
}

void screenController (void * param) {
  displayInit();
  //loop to control display elements
  while (true) {
    if (pros::competition::is_disabled()) status = "Disabled";
    else if (pros::competition::is_autonomous()) status = "Autonomous";
    else status = "Driver Control";
    lv_label_set_text(competitionStatus, status.c_str());
    lv_obj_align(competitionStatus, telemetryTab, LV_ALIGN_CENTER, 0, 0);
    pros::Task::delay(500);
  }
}

void initialize () {
  // initialize the display and control display elements
  pros::Task screenTask (screenController);
}


// currnetly not using these functions
void disabled () {}

void competition_initialize () {}
