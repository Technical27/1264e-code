#include "include.hpp"

// Loads a auton from a file
void loadAuton (const char* filename) {
  FILE* file = fopen(filename, "r");
  std::unique_ptr<double[]> doubles;
  while (!feof(file)) {
    doubles = std::make_unique<double[]>(4);
    fread(doubles.get(), sizeof(double), 4, file);
    loadedAuton.push_back(std::move(doubles));
  }
}