///
/// Input Stream reading function
/// definitions
///
#include <istream>
#include <unordered_map>
#include "token.h"
#include "../util/stl.h"



///
/// Reads an identifier from the given
/// input stream, assuming that the current
/// character is a valid identifier character.
/// The read stops when an excluded character
/// (present in the exclusions map) is found
///
std::string read_identifier(
  std::istream* input,
  char* current,
  exclude_map exclusions
);

///
/// Reads a string from the given
/// input stream, assuming that the current
/// character is a double quote. The
/// read stops when an excluded character
/// (present in the exclusions map) is found
///
std::string read_quoted_string(
    std::istream* input,
    char* current,
    exclude_map exclusions
); 

///
/// Skips spaces in the given
/// input stream without checking
/// if the current character is a
/// space or a line break
///
inline void skip_spaces(std::istream* input, char* current) {
  while (is_space_or_break(*current = input->get())) {};
}

///
/// Skips spaces in the given
/// input stream checking if the
/// current character is a space
/// or a line break
///
inline void skip_spaces_checked(std::istream* input, char* current) {
  if (is_space_or_break(*current)) {
    *current = input->get();
    skip_spaces(input, current);
  }
}
