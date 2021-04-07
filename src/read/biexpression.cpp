#include "biexpression.h"
#include "streamr.h"

/**
 * Reads a binary expression from the
 * given input stream, changes the current value
 * while reading the expression and
 * stops when a prohibited or an excluded
 * char is found
 */
BinaryExpression read_binary_expr(
    std::istream* input,
    char* current,
    exclude_map exclusions
) {

}