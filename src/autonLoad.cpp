/*
  Contains a function to load autonomous from an sd card

  Copyright (c) 2019 Aamaruvi Yogamani
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "include.hpp"

// Loads a auton from a file
bool loadAuton (const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == nullptr) {
    debugLog("Error when opening file:\n");
    debugLog(strerror(errno));
    return false;
  }
  while (!feof(file)) {
    std::unique_ptr<double[]> doubles (new double[4]);
    fread(doubles.get(), sizeof(double), 4, file);
    loadedAuton.push_back(std::move(doubles));
  }
  fclose(file);
  return true;
}
