#include "include.hpp"

// Function to draw a rectangle
std::unique_ptr<lv_obj_t> drawRect(int x, int y, int w, int h, lv_color_t color, lv_obj_t* parent) {
  std::unique_ptr<lv_obj_t> obj1 (lv_obj_create(parent, NULL));
  std::unique_ptr<lv_style_t> style (new lv_style_t);
  lv_style_copy(style.get(), &lv_style_plain_color);

  style->body.empty = 1;
  style->body.border.color = color;
  style->body.border.width = 1;
  style->body.border.part = LV_BORDER_FULL;

  lv_obj_set_style(obj1.get(), style.get());

  lv_obj_set_pos(obj1.get(), x, y);
  lv_obj_set_size(obj1.get(), w, h);

  return obj1;
}

// Function to control the display
void screenControl (void*) {
  int selectedAuton = 1;
  bool auton = false;

  lv_obj_t* autonSection = drawRect(0, 0, 100, 100, LV_COLOR_RED, lv_scr_act()).get();
  lv_obj_t* currentAuton = lv_label_create(autonSection, NULL);

  // Declared to -1 to force a screen update to initially draw the text
  int currentSelectedAuton = -1;
  std::unique_ptr<char[]> buf (new char[20]);
  while (true) {
    // Menu button handler
    if (menuLeft.changedToPressed() && selectedAuton > 1) selectedAuton--;
    else if (menuRight.changedToPressed() && selectedAuton < 3) selectedAuton++;
    // Screen updater
    if (currentSelectedAuton != selectedAuton) {
      currentSelectedAuton == selectedAuton;
      sprintf(buf.get(), "Current selected auton: %d", currentSelectedAuton);
      lv_label_set_text(currentAuton, buf.get());
      lv_obj_set_pos(currentAuton, 10, 10);
      buf = std::make_unique<char[]>(20);
    }
    pros::Task::delay(50);
  };
}