#include <unordered_map>

// #define __2Q_PROD

/**
 * The map used to store the
 * character exclusions, works
 * as a constant-access character
 * stack
 */
using exclude_map = std::unordered_map<char, int>;