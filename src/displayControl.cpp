#include "include.hpp"

lv_obj_t* errorArea;

void debugLog (const char* text) {
  lv_ta_add_text(errorArea, text);
}

void screenControl (void*) {
  errorArea = lv_ta_create(lv_scr_act(), nullptr);
  lv_obj_set_size(errorArea, 300, 100);
  lv_obj_align(errorArea, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
}
