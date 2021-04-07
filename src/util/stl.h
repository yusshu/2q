/**
 * Utility functions for working with
 * classes from the STL (Standard
 * Template Library)
 */
#include <unordered_set>
#include <unordered_map>

/**
 * The map used to store the
 * character exclusions, works
 * as a constant-access character
 * stack
 */
using exclude_map = std::unordered_map<char, int>;

/**
 * Adds or increases the already present value
 * linked to the given key in the specified map
 */
inline void put_or_increase(exclude_map map, char key) {
  auto result = map.find(key);
  map[key] = result == map.end() ? 1 : result->second + 1;
}

/**
 * Checks if the given key exists in the
 * specified map, if it exists, then the
 * value is decreased, if new value is zero,
 * it's removed
 * @return True if key was present in the map
 */
inline bool check_and_decrease(exclude_map map, char key) {
  auto result = map.find(key);
  if (result == map.end()) {
    return false;
  } else {
    int value = result->second - 1;
    if (value <= 0) {
      map.erase(result);
    } else {
      map[key] = value;
    }
    return true;
  }
}