///
/// Input Stream reading function
/// definitions
///
#include <istream>
#include <unordered_map>
#include "token.h"
#include "../core.h"
#include "expression.h"
#include "ctx.h"


Expression* read_expression(ParseContext& context);

Expression* read_binary_expr(ParseContext& context, Expression* first);

///
/// Reads an identifier from the given
/// input stream, assuming that the current
/// character is a valid identifier character.
/// The read stops when an excluded character
/// (present in the exclusions map) is found
///
std::string read_identifier(ParseContext& context);

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
