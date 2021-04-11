#include "expression.h"
#include "streamr.h"

Expression *read_expression(ParseContext &context) {
  context.skip_spaces();
  char current = context.current;
  // wrapped expression
  if (current == '(') {
    ++context;
    // add the ')' as exclusion
    context.push_exclusion(')');
    Expression *expr = read_expression(context);
    // assert it's closed
    context.assert_exclusion(')');
    return expr;
  } else if (is_letter_or_underscore(current)) {
    std::string identifier;
    identifier.push_back(current);
    while (is_letter_or_underscore((current = ++context))) {
      identifier.push_back(current);
    }
    context.skip_spaces();
    return new LiteralExpression<std::string>(identifier);
  } else if (is_number(current)) {
    int value = current - '0';
    while (is_number((current = ++context))) {
      value *= 10;
      value += current - '0';
    }
    context.skip_spaces();
    return new LiteralExpression<int>(value);
  } else {
    throw ParseError("Cannot parse huh");
  }
}

Expression* read_eqsuffixed_expr(
    ParseContext& context,
    Expression* first,
    BinaryExpression::Kind simpleKind,
    BinaryExpression::Kind assignationKind
) {
  // Skip the operator and check if next
  // is a '=' then skip spaces on both cases
  BinaryExpression::Kind kind;
  if (++context == '=') {
    context.skip_next_spaces();
    kind = assignationKind;
  } else {
    context.skip_spaces();
    kind = simpleKind;
  }
  // Read the right expression
  Expression* second = read_expression(context);
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
Expression* read_binary_expr(ParseContext& context, Expression* first) {
  char current = context.current;
  if (current == '[') {
    // Skip the '[' and the next spaces
    context.skip_next_spaces();
    // Add the ']' as exclusion
    context.push_exclusion('[');
    // Read the right expression
    Expression* second = read_expression(context);
    // Assert that the current character is ']'
    context.assert_exclusion(']');
    // Finally we have the indexing expression
    return new BinaryExpression(first, second, BinaryExpression::Kind::INDEXING);
  } else if (current == '+') {
    // check for addition
    return read_eqsuffixed_expr(
        context, first,
        BinaryExpression::Kind::ADD, BinaryExpression::Kind::ASSIGN_ADD
    );
  } else if (current == '-') {
    // check for subtraction
    return read_eqsuffixed_expr(
        context, first,
        BinaryExpression::Kind::SUBTRACT, BinaryExpression::Kind::ASSIGN_SUBTRACT
    );
  } else if (current == '*') {
    // check for multiplication
    return read_eqsuffixed_expr(
        context, first,
        BinaryExpression::Kind::MULTIPLY, BinaryExpression::Kind::ASSIGN_MULTIPLY
    );
  } else if (current == '/') {
    // check for division
    return read_eqsuffixed_expr(
        context, first,
        BinaryExpression::Kind::DIVIDE, BinaryExpression::Kind::ASSIGN_DIVIDE
    );
  } else if (current == '=') {
    // check for comparison, this isn't really
    // an "assignable" binary expression, but it
    // it works as expected
    return read_eqsuffixed_expr(
        context, first,
        BinaryExpression::Kind::ASSIGN, BinaryExpression::Kind::EQUALITY
    );
  } else if (current == '!') {
    // Skip the operator and check if next
    // is a '=' then skip spaces
    if ((current = ++context) == '=') {
      context.skip_next_spaces();
    } else {
      std::string cause = "Unexpected token: '";
      cause += current;
      cause += "' Did you mean '='?";
      throw ParseError(cause.c_str());
    }
    // Read the right expression
    Expression* second = read_expression(context);
    // Finally we have the assign-operate or operate expression
    return new BinaryExpression(first, second, BinaryExpression::Kind::INEQUALITY);
  } else if (current == '?') {
    // Skip the '?' and check if next
    // is a '?' then skip spaces in both cases
    if (++context == '?') {
      context.skip_next_spaces();
      // so it's nullability coalescing operator
      Expression* second = read_expression(context);
      // Finally we have the expression!
      return new BinaryExpression(first, second, BinaryExpression::Kind::NULL_COALESCING);
    } else {
      // TODO: Move this or rename the function, this isn't a binary expression
      context.skip_spaces();
      // so check if it's ternary expression

      // push the ':' character as exclusion
      context.push_exclusion(':');
      // read the truth value
      Expression* truthVal = read_expression(context);
      // assert that the character is a ':'
      context.assert_exclusion(':');
      // read the false value
      Expression* falseVal = read_expression(context);
      return new TernaryExpression(first, truthVal, falseVal);
    }
  } else {
    // cannot parse as a binary expression
    context.skip_spaces();
    return nullptr;
  }
}