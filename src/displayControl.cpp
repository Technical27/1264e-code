#include "include.hpp"


// Function to draw a rectangle
lv_obj_t* drawRect(int x, int y, int w, int h, lv_color_t color, lv_obj_t* parent) {
  lv_obj_t* obj1 = lv_obj_create(parent, NULL);
  lv_style_t* style = new lv_style_t;
  lv_style_copy(style, &lv_style_plain_color);

  style->body.empty = 1;
  style->body.border.color = color;
  style->body.border.width = 1;
  style->body.border.part = LV_BORDER_FULL;

  lv_obj_set_style(obj1, style);
  delete style;

  lv_obj_set_pos(obj1, x, y);
  lv_obj_set_size(obj1, w, h);

  return obj1;
}


// Function to control the display
void screenControl (void* param) {
  int selectedAuton = 1;
  bool auton = false;

  lv_obj_t* autonSection = drawRect(0, 0, 100 , 100, LV_COLOR_RED, lv_scr_act());
  lv_obj_t* currentAuton = lv_label_create(autonSection, NULL);

  // Declared to -1 to force a screen update to initially draw the text
  int currentSelectedAuton = -1;
  char* buf = new char[20];
  while (true) {
    // Menu button handler
    if (menuLeft.changedToPressed() && selectedAuton > 1) selectedAuton--;
    else if (menuRight.changedToPressed() && selectedAuton < 3) selectedAuton++;
    // Screen updater
    if (currentSelectedAuton != selectedAuton) {
      currentSelectedAuton == selectedAuton;
      sprintf(buf, "Current selected auton: %d", currentSelectedAuton);
      lv_label_set_text(currentAuton, buf);
      lv_obj_set_pos(currentAuton, 10, 10);
      delete[] buf;
      buf = new char[20];
    }
    pros::Task::delay(50);
  };
}