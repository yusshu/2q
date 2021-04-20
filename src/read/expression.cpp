#include "expression.h"
#include "streamr.h"

Expression* read_simple_expr(ParseContext& context) {

  //#region wrapped expression
  if (context.current == '(') {
    // skip the current '(' and next spaces
    context.skip_next_spaces();
    // add the ')' as exclusion
    context.push_exclusion(')');
    Expression *expr = read_expression(context);
    // assert it's closed
    context.assert_exclusion(')');
    return expr;
  }
  //#endregion

  //#region identifier and literal boolean expressions
  if (is_letter_or_underscore(context.current)) {
    std::string identifier;
    identifier.push_back(context.current);
    while (is_letter_or_underscore(++context)) {
      identifier.push_back(context.current);
    }
    context.skip_spaces();

    // check if it's a literal keyword
    if (identifier == "true") {
      return new LiteralExpression<bool>(true);
    } else if (identifier == "false") {
      return new LiteralExpression<bool>(false);
    } else {
      return new IdentifierExpression(identifier);
    }
  }
  //#endregion

  //#region string literal expression
  if (context.current == '"') {
    std::string value;
    while (++context != '"') {
      value.push_back(context.current);
    }
    context.skip_next_spaces(); // skip the last double quote and next spaces
    return new LiteralExpression<std::string>(value);
  }
  //#endregion

  //#region number literal expression
  if (is_number(context.current)) {
    int value = context.current - '0';
    while (is_number((context.current = ++context))) {
      value *= 10;
      value += context.current - '0';
    }
    context.skip_spaces();
    return new LiteralExpression<int>(value);
  }
  //#endregion

  return nullptr;
}

Expression* read_expression(ParseContext &context) {
  context.skip_spaces();
  Expression* expr = read_simple_expr(context);
  if (expr == nullptr) {
    return expr;
  } else {
    while (!context.check_exclusion(context.current) && !is_space_or_break(context.current)) {
      expr = read_binary_expr(context, expr);
    }
    return expr;
  }
}

Expression* read_term(ParseContext& context, Expression* first) {
  if (context.current == '*') {
    // skip the current '*' and next spaces
    context.skip_next_spaces();
    // read the second expression
    Expression* second = read_simple_expr(context);
    return new BinaryExpression(first, second, BinaryExpression::Kind::MULTIPLY);
  }
  return first;
}

Expression* read_add(ParseContext& context, Expression* first) {
  if (context.current == '+') {
    // skip the current '+' and next spaces
    context.skip_next_spaces();
    // read simple expr or term if present
    Expression* second = read_term(context, read_simple_expr(context));
    return new BinaryExpression(first, second, BinaryExpression::Kind::ADD);
  } else {
    return read_term(context, first);
  }
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
  if (current == '.') {
    // Skip the '.' and the next spaces
    context.skip_next_spaces();
    // Read the second expression
    Expression* second = read_expression(context);
    return new BinaryExpression(first, second, BinaryExpression::Kind::DOT);
  } else if (current == '[') {
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
      Expression *second = read_expression(context);
      // Finally we have the expression!
      return new BinaryExpression(first, second, BinaryExpression::Kind::NULL_COALESCING);
    } else {
      // TODO: Move this or rename the function, this isn't a binary expression
      context.skip_spaces();
      // so check if it's ternary expression

      // push the ':' character as exclusion
      context.push_exclusion(':');
      // read the truth value
      Expression *truthVal = read_expression(context);
      // assert that the character is a ':'
      context.assert_exclusion(':');
      // read the false value
      Expression *falseVal = read_expression(context);
      return new TernaryExpression(first, truthVal, falseVal);
    }
  } else if (current == '(') {
    context.skip_next_spaces();
    context.push_exclusion(')');
    std::vector<Expression*> args;
    while (context.current != ')') {
      context.push_exclusion(',');
      Expression* arg = read_expression(context);
      args.push_back(arg);
      context.skip_spaces();
      if (context.current == ')') {
        break;
      } else {
        context.assert_exclusion(',');
      }
    }
    context.assert_exclusion(')');
    return new FunctionCallExpression(first, args);
  } else {
    // cannot parse as a binary expression
    context.skip_spaces();
    return read_add(context, first);
  }
}