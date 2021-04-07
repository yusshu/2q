///
/// Utility functions for working with
/// classes from the STL (Standard 
/// Template Library)
///
#include <unordered_set>
#include <unordered_map>

template <class T>
inline void put_or_increase(std::unordered_map<T, int> map, T key) {
  auto result = map.find(key);
  int newValue;
  if (result == map.end()) {
    newValue = 1;
  } else {
    newValue = result->second + 1;
  }
  map[key] = newValue;
}

template <class T>
inline bool check_and_decrease(std::unordered_map<T, int> map, T key) {
  auto result = map.find(key);
  if (result == map.end()) {
    return false;
  } else {
    map[key] = result->second;
    return true;
  }
}

template <class T>
inline bool has(std::unordered_set<T> set, T element) {
  return set.find(element) != set.end();
}