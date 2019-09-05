#include "main.h"
#include <memory>
#include <vector>
#include <cstdio>

// Individual motors
extern Motor frontLeft;
extern Motor frontRight;
extern Motor backLeft;
extern Motor backRight;
extern Motor claw;

// Left and right motor groups
extern MotorGroup left;
extern MotorGroup right;

// Chassis
extern ChassisControllerIntegrated chassis;

// The main controller
extern Controller mainController;

// Currently loaded auton
extern std::vector<std::unique_ptr<double[]>> loadedAuton;

extern bool autonLoaded;

// Task functions
void screenControl (void*);

// Error output
extern lv_obj_t* errorArea;

void debugLog(const char* text);

bool loadAuton (const char* filename);
