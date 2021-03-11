///
/// Utility functions for working with
/// classes from the STL (Standard 
/// Template Library)
///
#include <unordered_set>

template <class T>
inline bool has(std::unordered_set<T> set, T element) {
  return set.find(element) != set.end();
}