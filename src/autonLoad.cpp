#include "include.hpp"

// Loads a auton from a file
bool loadAuton (const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file === NULL) return false;
  while (!feof(file)) {
    std::unique_ptr<double[]> doubles (new double[4]);
    fread(doubles.get(), sizeof(double), 4, file);
    loadedAuton.push_back(std::move(doubles));
  }
  fclose(file);
  return true;
}
