///
/// Definitions for ANSI escape color
/// codes for logging information
///
#pragma once

// Normal Colors
#define BLACK "\u001b[30m"
#define RED "\u001b[31m"
#define GREEN "\u001b[32m"
#define YELLOW "\u001b[33m"
#define BLUE "\u001b[34m"
#define MAGENTA "\u001b[35m"
#define CYAN "\u001b[36m"
#define WHITE "\u001b[37m"

// Bright Colors
#define BRIGHT_BLACK "\u001b[30;1m"
#define BRIGHT_RED "\u001b[31;1m"
#define BRIGHT_GREEN "\u001b[32;1m"
#define BRIGHT_YELLOW "\u001b[33;1m"
#define BRIGHT_BLUE "\u001b[34;1m"
#define BRIGHT_MAGENTA "\u001b[35;1m"
#define BRIGHT_CYAN "\u001b[36;1m"
#define BRIGHT_WHITE "\u001b[37;1m"

// Background Normal Colors
#define BG_BLACK "\u001b[40m"
#define BG_RED "\u001b[41m"
#define BG_GREEN "\u001b[42m"
#define BG_YELLOW "\u001b[43m"
#define BG_BLUE "\u001b[44m"
#define BG_MAGENTA "\u001b[45m"
#define BG_CYAN "\u001b[46m"
#define BG_WHITE "\u001b[47m"

// Background Bright Colors
#define BG_BRIGHT_BLACK "\u001b[40;1m"
#define BG_BRIGHT_RED "\u001b[41;1m"
#define BG_BRIGHT_GREEN "\u001b[42;1m"
#define BG_BRIGHT_YELLOW "\u001b[43;1m"
#define BG_BRIGHT_BLUE "\u001b[44;1m"
#define BG_BRIGHT_MAGENTA "\u001b[45;1m"
#define BG_BRIGHT_CYAN "\u001b[46;1m"
#define BG_BRIGHT_WHITE "\u001b[47;1m"

// Reset
#define RESET "\u001b[0m"