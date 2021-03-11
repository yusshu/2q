#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/color.h"
#include "../include/log.h"
#include "../include/pmodel.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    // TODO: Initialize the CLI
    info("> Initializing CLI...");
    return 0;
  } else if (argc > 2) {
    error("< Too many arguments!");
    return 1;
  } else {
    if (std::strcmp(argv[1], "build") == 0) {
      /// Starts the build and checks
      /// for the project model (PM)
      /// file in the current working directory
      info("> Starting build...");
      std::ifstream pm_input(PM_FILE_NAME);

      if (!pm_input.is_open()) {
        error("< Project-model-file not found in the current working directory");
        return 1;
      }

      ProjectModel model(&pm_input); 

      
      return 0;
    } else {
      error("< Unknown operation");
      return 1;
    }
  }
}