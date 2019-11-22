/*
  Contains macros for display code

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
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

#define CreateAutonHandle(scr, mode, number) \
  lv_res_t scr##number##Handle (lv_obj_t* btn, lv_signal_t e, void*) { \
    if (e == LV_SIGNAL_PRESSED && lastScrChange + 100 < pros::millis()) { \
      if (btn == selectedAutonBtn) { \
        currentAuton = 0; \
        autonMode = 0; \
        lv_obj_set_style(btn, &mainStyle); \
        selectedAutonBtn = nullptr; \
      } \
      else { \
        currentAuton = number; \
        autonMode = mode; \
        if (selectedAutonBtn != nullptr) lv_obj_set_style(selectedAutonBtn, &mainStyle); \
        lv_obj_set_style(btn, &selectedAutonStyle); \
        selectedAutonBtn = btn; \
      } \
      lastScrChange = pros::millis(); \
    } \
    return LV_RES_OK; \
  }

#define CreateAuton(scr, number, align) \
  CreateBtn(scr##number, scr, nullptr, #number, LV_HOR_RES/2, LV_VER_RES/2) \
  lv_obj_set_signal_func(scr##number, scr##number##Handle); \
  lv_obj_align(scr##number, nullptr, align, 0, 0); \
