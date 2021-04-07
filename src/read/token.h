///
/// Utility functions for
/// working with characters
///

inline bool is_space_or_break(char c) {
  return c == ' ' || c == '\n';
}

inline bool is_number(char c) {
  return c >= '0' && c <= '9';
}

inline bool is_letter(char c) {
  return (c >= 'a' && 'z' >= c) || (c >= 'A' && 'Z' >= c);
}