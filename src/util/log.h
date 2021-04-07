#pragma once
#include <string>


/**
 * Logs the given message to the
 * standard output using green color
 */
void info(const std::string& message);

/**
 * Logs the given message to the
 * standard output using red color
 */
void error(const std::string& message);