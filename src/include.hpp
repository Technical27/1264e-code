#include "main.h"
#include <memory>
#include <vector>
#include <stdio.h>

// Individual motors
extern Motor frontLeft;
extern Motor frontRight;
extern Motor backLeft;
extern Motor backRight;

// Left and right motor groups
extern MotorGroup left;
extern MotorGroup right;

// menu buttons
extern ADIButton menuLeft;
extern ADIButton menuRight;

// The main controller
extern Controller mainController;

// Mutex for motor access
extern pros::Mutex motorMutex;

// Currently loaded auton
extern std::vector<std::unique_ptr<double[]>> loadedAuton;

// Task functions
void driveControl (void*);
void strafeControl (void*);
void screenControl (void*);

void loadAuton (const char* filename);