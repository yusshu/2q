#include "biexpression.h"
#include "streamr.h"
#include "ctx.h"

BinaryExpression read_assignable_binary_expr(
    ParseContext& context,
    const Expression& first,
    BinaryExpression::Kind simpleKind,
    BinaryExpression::Kind assignationKind
) {
  // Skip the operator and check if next
  // is a '=' then skip spaces on both cases
  BinaryExpression::Kind kind;
  if ((current = ++context) == '=') {
    context.skip_next_spaces();
    kind = assignationKind;
  } else {
    context.skip_spaces();
    kind = simpleKind;
  }
  // Read the right expression
  const Expression& second = read_expression(context);
  // Finally we have the assign-operate or operate expression
  return new BinaryExpression(first, second, kind);
}

/**
 * Reads a binary expression from the
 * given input stream, changes the current value
 * while reading the expression and
 * stops when a prohibited or an excluded
 * char is found.
 *
 * This function assumes that the current character
 * is a non-dummy character and it's not part of the
 * first expression
 */
BinaryExpression read_binary_expr(ParseContext& context, const Expression& first) {
  char current = context.current;
  if (current == '[') {
    // Skip the '[' and the next spaces
    current = context.skip_next_spaces();
    // Add the ']' as exclusion
    context.push_exclusion('[');
    // Read the right expression
    const Expression& second = read_expression(context);
    // Assert that the current character is ']'
    context.assert_exclusion(']');
    // Finally we have the indexing expression
    return BinaryExpression(first, second, BinaryExpression::Kind::INDEXING);
  } else if (current == '+') {
    // check for addition
    return read_assignable_binary_expr(
        context, first,
        BinaryExpression::Kind::ADD, BinaryExpression::Kind::ASSIGN_ADD
    );
  } else if (current == '-') {
    // check for subtraction
    return read_assignable_binary_expr(
        context, first,
        BinaryExpression::Kind::SUBTRACT, BinaryExpression::Kind::ASSIGN_SUBTRACT
    );
  } else if (current == '*') {
    // check for multiplication
    return read_assignable_binary_expr(
        context, first,
        BinaryExpression::Kind::MULTIPLY, BinaryExpression::Kind::ASSIGN_MULTIPLY
    );
  } else if (current == '/') {
    // check for division
    return read_assignable_binary_expr(
        context, first,
        BinaryExpression::Kind::DIVIDE, BinaryExpression::Kind::ASSIGN_DIVIDE
    );
  } else if (current == '=') {
    // check for comparison, this isn't really
    // an "assignable" binary expression, but it
    // it works as expected
    return read_assignable_binary_expr(
        context, first,
        BinaryExpression::Kind::ASSIGN, BinaryExpression::Kind::EQUALITY
    );
  } else if (current == '!') {

  }
}