#pragma once
#include <string>
#include <iostream>
#include "color.h"

/**
 * Logs the given message to the
 * standard output using green color
 */
void info(const std::string& message) {
  std::cout << BRIGHT_GREEN << message << RESET << std::endl;
}

/**
 * Logs the given message to the
 * standard output using red color
 */
void error(const std::string& message) {
  std::cout << BRIGHT_RED << message << RESET << std::endl;
}