#include "log.h"
#include <iostream>
#include "color.h"

void info(const std::string& message) {
  std::cout << BRIGHT_GREEN << message << RESET << std::endl;
}

void error(const std::string& message) {
  std::cout << BRIGHT_RED << message << RESET << std::endl;
}