#include "streamr.h"
#include "../core.h"

///
/// Reads an identifier until a space, a 
/// line break or an excluded character
/// is found
///
std::string read_identifier(ParseContext& context) {
  std::string value;
  while (true) {
    if (is_space_or_break(context.current)) {
      // To give the next read a valid char
      context.skip_next_spaces();
      break;
    } else if (context.input.eof()) {
      break;
    } else {
      value.push_back(context.current);
      if (context.check_exclusion(++context)) {
        break;
      }
    }
  }
  return value;
}