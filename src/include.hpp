/*
  Main header that externs many variables and includes more headers

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "main.h"
#include <memory>
#include <vector>
#include <cstdio>
#include <cstring>

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

// Current selected auton
extern int currentAuton;
extern int currentSide;

// Current mode
extern int mode;

// Task functions
void screenControl (void*);

// Error output
void debugLog (const char* text);

// Obama image
void loadObama ();

// Main screen
void loadMain ();
