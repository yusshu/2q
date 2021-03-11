#include "../include/log.h"
#include "../include/color.h"
#include <iostream>

void info(std::string message) {
  std::cout << BRIGHT_GREEN << message << RESET << std::endl;
}

void error(std::string message) {
  std::cout << BRIGHT_RED << message << RESET << std::endl;
}