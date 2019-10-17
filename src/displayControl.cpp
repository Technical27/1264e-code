/*
  Contains a task to control the V5 display

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

int lastScrChange = pros::millis();

#define DefineBtn(name) \
  lv_obj_t* name; \
  lv_obj_t* name##Label;

#define CreateBtn(name, par, cpy, label, w, h) \
  name = lv_btn_create(par, cpy); \
  name##Label = lv_label_create(name, nullptr); \
  lv_label_set_text(name##Label, label); \
  lv_obj_set_size(name, w, h); \
  lv_obj_align(name##Label, name, LV_ALIGN_CENTER, 0, 0); \
  lv_obj_set_signal_func(name, name##Handle); 

#define CreateBtnHandle(name, scr) \
  lv_res_t name##Handle (lv_obj_t*, lv_signal_t e, void*) { \
    if(e == LV_SIGNAL_LONG_PRESS) { \
      lv_scr_load(scr); \
      lastScrChange = pros::millis(); \
    } \
    return LV_RES_OK; \
  }

#define CreateScr(scr) \
  scr = lv_obj_create(nullptr, nullptr); \
  lv_obj_set_style(scr, &mainStyle);

lv_style_t mainStyle;

LV_IMG_DECLARE(obama)
lv_obj_t* obamaImg;

std::string buf;

lv_obj_t* errorArea;
lv_obj_t* scr;
lv_obj_t* dbg;
lv_obj_t* auton;
lv_obj_t* obamaScr;

DefineBtn(dbgToMain)
DefineBtn(mainToDbg)

DefineBtn(mainToAuton)
DefineBtn(autonToMain)

DefineBtn(autonMode)
DefineBtn(autonSide)

CreateBtnHandle(dbgToMain, scr)
CreateBtnHandle(mainToDbg, dbg)

CreateBtnHandle(mainToAuton, auton)
CreateBtnHandle(autonToMain, scr)

int currentAuton = 1;
const char* autonModes[] = {"Off", "Blue", "Red", "Skills"};

int currentSide = 0;
const char* autonSides[] = {"Left", "Right"};

void initStyle () {
  lv_style_copy(&mainStyle, &lv_style_plain);

  mainStyle.body.border.color = LV_COLOR_MAKE(0xEB, 0x8D, 0x00);
  mainStyle.body.border.width = 3;
  mainStyle.body.border.part = LV_BORDER_FULL;
  mainStyle.body.radius = 10;

  mainStyle.body.main_color = LV_COLOR_BLACK;
  mainStyle.body.grad_color = mainStyle.body.main_color;

  mainStyle.text.color = LV_COLOR_BLACK;
}

lv_res_t autonModeHandle (lv_obj_t*, lv_signal_t e, void*) {
  if (e == LV_SIGNAL_PRESSED && lastScrChange + 100 < pros::millis()) {
    if (++currentAuton > 3) currentAuton = 0;
    lv_label_set_text(autonModeLabel, autonModes[currentAuton]);
  }
  return LV_RES_OK;
}

lv_res_t autonSideHandle (lv_obj_t*, lv_signal_t e, void*) {
  if (e == LV_SIGNAL_PRESSED && lastScrChange + 100 < pros::millis()) {
    if (++currentSide > 1) currentSide = 0;
    lv_label_set_text(autonSideLabel, autonSides[currentSide]);
  }
  return LV_RES_OK;
}

void debugLog (const char* text) {
  if (errorArea != nullptr) lv_ta_add_text(errorArea, text);
  else buf += text;
}

void loadObama () {
  if (obamaScr != nullptr) lv_scr_load(obamaScr);
}

void loadMain () {
  if (scr != nullptr) lv_scr_load(scr);
}

void screenControl (void*) {
  initStyle();
  CreateScr(scr)
  CreateScr(dbg)
  CreateScr(auton)
  CreateScr(obamaScr)

  lv_scr_load(scr);

  CreateBtn(mainToDbg, scr, nullptr, "Debug", LV_HOR_RES/2, LV_VER_RES/2)
  lv_obj_align(mainToDbg, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  CreateBtn(dbgToMain, dbg, nullptr, "Back to Main", LV_HOR_RES/4, LV_VER_RES/8)
  lv_obj_align(dbgToMain, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  CreateBtn(mainToAuton, scr, mainToDbg, "Auton", LV_HOR_RES/2, LV_VER_RES/2);
  lv_obj_align(mainToAuton, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

  CreateBtn(autonToMain, auton, dbgToMain, "Back to Main", LV_HOR_RES/4, LV_VER_RES/8);

  CreateBtn(autonMode, auton, nullptr, "Blue", LV_HOR_RES/2, LV_VER_RES/2)
  lv_obj_align(autonMode, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, LV_VER_RES/8);
  autonModeHandle(nullptr, LV_SIGNAL_PRESS_LOST, autonModeLabel);

  CreateBtn(autonSide, auton, autonMode, "Left", LV_HOR_RES/2, LV_VER_RES/2);
  lv_obj_align(autonSide, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, LV_VER_RES/8);
  autonModeHandle(nullptr, LV_SIGNAL_PRESS_LOST, autonSideLabel);

  errorArea = lv_ta_create(dbg, nullptr);
 
  lv_obj_set_size(errorArea, LV_HOR_RES, LV_VER_RES);
  lv_obj_align(errorArea, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, LV_VER_RES/8);
  lv_ta_set_text(errorArea, "");
  lv_ta_set_cursor_type(errorArea, LV_CURSOR_NONE);

  debugLog(buf.c_str());
  debugLog("Finished Initalizing Display\n");

  lv_obj_t* obamaImg = lv_img_create(obamaScr, nullptr);
  lv_img_set_src(obamaImg, &obama);
  lv_obj_align(obamaImg, nullptr, LV_ALIGN_CENTER, 0, 0);
  if (mode != 0) lv_scr_load(obamaScr);
}
