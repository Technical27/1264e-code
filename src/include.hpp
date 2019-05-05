#include "main.h"

extern Motor frontLeft;
extern Motor frontRight;
extern Motor backLeft;
extern Motor backRight;

extern MotorGroup left;
extern MotorGroup right;

extern Controller mainController;

extern pros::Mutex motorMutex;

void driveControl (void* param);
void strafeControl (void* param);