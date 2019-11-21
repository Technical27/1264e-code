/*
  Contains a task to control the V5 display

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

int lastScrChange = pros::millis();

int currentAuton = 0;
int autonMode = 0;

#define DefineBtn(name) \
  lv_obj_t* name; \
  lv_obj_t* name##Label;

#define CreateBtn(name, par, cpy, label, w, h) \
  name = lv_btn_create(par, cpy); \
  name##Label = lv_label_create(name, nullptr); \
  lv_label_set_text(name##Label, label); \
  lv_obj_set_size(name, w, h); \
  lv_obj_align(name##Label, name, LV_ALIGN_CENTER, 0, 0); \
  lv_obj_set_style(name, &mainStyle); \
  lv_obj_set_signal_func(name, name##Handle); 

#define CreateBtnHandle(name, scr) \
  lv_res_t name##Handle (lv_obj_t*, lv_signal_t e, void*) { \
    if(e == LV_SIGNAL_PRESSED && lastScrChange + 100 < pros::millis()) { \
      lv_scr_load(scr); \
      lastScrChange = pros::millis(); \
    } \
    return LV_RES_OK; \
  }

#define CreateScr(scr) \
  scr = lv_obj_create(nullptr, nullptr); \
  lv_obj_set_style(scr, &mainStyle);

#define CreateAutonScrHandle(name) \
  lv_res_t name##Handle (lv_obj_t*, lv_signal_t e, void*) { \
    if (e == LV_SIGNAL_PRESSED && lastScrChange + 100 < pros::millis()) { \
      lv_scr_load(name##Scr); \
      lastScrChange = pros::millis(); \
    } \
    return LV_RES_OK; \
  }

#define CreateAutonBackToMain(name, par) \
  name = lv_btn_create(par, nullptr); \
  name##Label = lv_label_create(name, nullptr); \
  lv_label_set_text(name##Label, "Back to main"); \
  lv_obj_set_size(name, LV_HOR_RES/2, LV_VER_RES/2); \
  lv_obj_align(name##Label, name, LV_ALIGN_CENTER, 0, 0); \
  lv_obj_align(name, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0); \
  lv_obj_set_style(name, &mainStyle); \
  lv_obj_set_signal_func(name, name##Handle);

lv_obj_t* selectedAutonBtn;

#define CreateAutonHandle(scr, mode, number) \
  lv_res_t scr##number##Handle (lv_obj_t* btn, lv_signal_t e, void*) { \
    if (e == LV_SIGNAL_PRESSED && lastScrChange + 100 < pros::millis()) { \
      currentAuton = number; \
      autonMode = mode; \
      if (selectedAutonBtn != nullptr) lv_obj_set_style(selectedAutonBtn, &mainStyle); \
      lv_obj_set_style(btn, &selectedAutonStyle); \
      selectedAutonBtn = btn; \
      lastScrChange = pros::millis(); \
      return LV_RES_OK; \
    } \
  }

#define CreateAuton(scr, number, align) \
  CreateBtn(scr##number, scr, nullptr, #number, LV_HOR_RES/2, LV_VER_RES/2) \
  lv_obj_set_signal_func(scr##number, scr##number##Handle); \
  lv_obj_align(scr##number, nullptr, align, 0, 0); \

lv_style_t mainStyle, selectedAutonStyle;

LV_IMG_DECLARE(obama)

std::string buf;

lv_obj_t* errorArea;
lv_obj_t* scr;
lv_obj_t* dbg;

lv_obj_t* obamaScr;
lv_obj_t* autonRedScr;
lv_obj_t* autonBlueScr;
lv_obj_t* autonSkillsScr;

DefineBtn(dbgToMain)
DefineBtn(mainToDbg)

DefineBtn(autonRed)
DefineBtn(autonBlue)
DefineBtn(autonSkills)

DefineBtn(autonRedBack)
DefineBtn(autonBlueBack)
DefineBtn(autonSkillsBack)

DefineBtn(autonRedScr1);
DefineBtn(autonRedScr2);

DefineBtn(obamaBtn);

CreateBtnHandle(dbgToMain, scr)
CreateBtnHandle(mainToDbg, dbg)

CreateBtnHandle(obamaToMain, scr)

CreateAutonScrHandle(autonRed)
CreateAutonScrHandle(autonBlue)
CreateAutonScrHandle(autonSkills)

CreateAutonHandle(autonRedScr, 1, 1)
CreateAutonHandle(autonRedScr, 1, 2)

CreateBtnHandle(autonBlueBack, scr)
CreateBtnHandle(autonRedBack, scr)
CreateBtnHandle(autonSkillsBack, scr)


void initStyle () {
  lv_style_copy(&mainStyle, &lv_style_plain);

  mainStyle.body.border.color = LV_COLOR_MAKE(0xFF, 0x7B, 0x00);
  mainStyle.body.border.width = 3;
  mainStyle.body.border.part = LV_BORDER_FULL;
  mainStyle.body.radius = 10;

  mainStyle.body.main_color = LV_COLOR_BLACK;
  mainStyle.body.grad_color = mainStyle.body.main_color;

  mainStyle.text.color = LV_COLOR_MAKE(0xFF, 0x7B, 0x00);

  lv_style_copy(&selectedAutonStyle, &mainStyle);

  selectedAutonStyle.text.color = LV_COLOR_GRAY;
}

void debugLog (const char* text) {
  if (errorArea != nullptr) lv_ta_add_text(errorArea, text);
  else buf += text;
}

void loadObama () {
  if (obamaScr != nullptr) {
    pros::Task::delay(100);
    lv_scr_load(obamaScr);
  }
}

void loadMain () {
  if (scr != nullptr) lv_scr_load(scr);
}

lv_res_t obamaBtnHandle (lv_obj_t*, lv_signal_t e, void*) {
  if (lastScrChange + 100 < pros::millis() && e == LV_SIGNAL_PRESSING) {
    loadObama();
    lastScrChange = pros::millis();
  }
  return LV_RES_OK;
}

void screenControl (void*) {
  initStyle();
  CreateScr(scr)
  CreateScr(dbg)
  CreateScr(obamaScr)

  CreateScr(autonBlueScr)
  CreateScr(autonRedScr)
  CreateScr(autonSkillsScr)

  CreateAuton(autonRedScr, 1, LV_ALIGN_IN_TOP_LEFT)
  CreateAuton(autonRedScr, 2, LV_ALIGN_IN_TOP_RIGHT)

  lv_scr_load(scr);

  CreateBtn(mainToDbg, scr, nullptr, "Experimental", LV_HOR_RES/2, LV_VER_RES/2)
  lv_obj_align(mainToDbg, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);

  CreateBtn(dbgToMain, dbg, nullptr, "Back to Main", LV_HOR_RES/4, LV_VER_RES/4)
  lv_obj_align(dbgToMain, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  CreateBtn(autonRed, scr, nullptr, "Red", LV_HOR_RES/2, LV_VER_RES/2)
  lv_obj_align(autonRed, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  CreateBtn(autonBlue, scr, nullptr, "Blue", LV_HOR_RES/2, LV_VER_RES/2)
  lv_obj_align(autonBlue, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

  CreateBtn(autonSkills, scr, nullptr, "Skills", LV_HOR_RES/2, LV_VER_RES/2)
  lv_obj_align(autonSkills, nullptr, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

  CreateAutonBackToMain(autonRedBack, autonRedScr);
  CreateAutonBackToMain(autonBlueBack, autonBlueScr);
  CreateAutonBackToMain(autonSkillsBack, autonSkillsScr);

  errorArea = lv_ta_create(dbg, nullptr);
 
  lv_obj_set_size(errorArea, LV_HOR_RES, LV_VER_RES);
  lv_obj_align(errorArea, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, LV_VER_RES/4);
  lv_ta_set_text(errorArea, "");
  lv_ta_set_cursor_type(errorArea, LV_CURSOR_NONE);

  if (buf.length() > 0) debugLog(buf.c_str());
  debugLog("Finished Initalizing Display\n");

  lv_obj_t* obamaImg1 = lv_imgbtn_create(obamaScr, nullptr);
  lv_imgbtn_set_src(obamaImg1, LV_BTN_STATE_REL, &obama);
  lv_obj_align(obamaImg1, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_obj_set_signal_func(obamaImg1, obamaToMainHandle);

  lv_obj_t* obamaImg2 = lv_imgbtn_create(obamaScr, nullptr);
  lv_imgbtn_set_src(obamaImg2, LV_BTN_STATE_REL, &obama);
  lv_obj_align(obamaImg2, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
  lv_obj_set_signal_func(obamaImg2, obamaToMainHandle);

  CreateBtn(obamaBtn, dbg, nullptr, "Obama", LV_HOR_RES/4, LV_VER_RES/4);
  lv_obj_align(obamaBtn, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

  if (mode != 0) loadObama();
}
