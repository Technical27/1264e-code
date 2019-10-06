/*
  Contains a task to control the V5 display

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

lv_obj_t* errorArea;

void debugLog (const char* text) {
  lv_ta_add_text(errorArea, text);
}

void screenControl (void*) {
  errorArea = lv_ta_create(lv_scr_act(), nullptr);
  lv_obj_set_size(errorArea, LV_HOR_RES, LV_VER_RES);
  lv_obj_align(errorArea, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_ta_set_text(errorArea, "");
  lv_ta_set_cursor_type(errorArea, LV_CURSOR_NONE);
}
