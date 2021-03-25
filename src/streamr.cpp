#include "../include/streamr.h"
#include "../include/stlutil.h"

///
/// Reads a string until a space, a 
/// line break or an excluded character
/// is found
///
std::string read_quoted_string(
    std::istream* input,
    char* current,
    std::unordered_map<char, int> exclusions
) {
  std::string value;
  *current = input->get();
  while (true) {
    if (is_space_or_break(*current)) {
      // To give the next read a valid char
      skip_spaces(input, current);
      break;
    } else if (input->eof()) {
      break;
    } else {
      value.push_back(*current);
      *current = (char) input->get();
      if (check_and_decrease(exclusions, *current)) {
        break;
      }
    }
  }
  return value;
}