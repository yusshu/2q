#include "streamr.h"

Statement* read_conditional(ParseContext& context, Statement::Kind kind) {
  bool paren = context.current == '(';
  if (paren) {
    context.skip_next_spaces();
    context.push_exclusion(')');
  }
  context.push_exclusion('{');
  Expression* condition = read_expression(context);
  context.skip_spaces();
  if (paren) {
    context.assert_exclusion(')');
  }
  context.check_removing_exclusion('{');

  bool many = false;

  // if parenthesis are present, the curly braces aren't
  // required. If parenthesis aren't present, the curly braces
  // are required!
  if (!paren) {
    if (context.current != '{') {
      throw ParseError("Curly braces are required if you don't use parenthesis to wrap the conditional expression");
    } else {
      context.skip_next_spaces();
      many = true;
    }
  } else if (context.current == '{') {
    context.skip_next_spaces();
    many = true;
  }

  std::vector<Statement*> statements;

  if (many) {
    context.push_exclusion('}');
    while (context.current != '}') {
      statements.push_back(read_statement(context));
    }
    context.assert_exclusion('}');
  } else {
    statements.push_back(read_statement(context));
  }

  return new ConditionalStatement(kind, condition, statements);
}

Statement* read_statement(ParseContext& context) {
  context.skip_spaces();
  if (context.current == '{') {
    ++context;
    // add the ')' as exclusion
    context.push_exclusion('}');
    Statement* statement = read_statement(context);
    // assert it's closed
    context.assert_exclusion('}');
    return statement;
  } else if (context.check_exclusion(context.current)) {
    return nullptr;
  }

  std::string keyword;
  while (is_letter(context.current)) {
    keyword.push_back(context.current);
    ++context;
  }

  context.skip_spaces();

  if (keyword == "if") {
    return read_conditional(context, Statement::Kind::IF);
  } else if (keyword == "while") {
    return read_conditional(context, Statement::Kind::WHILE);
  } else {
    Expression* expr;
    if (keyword.length() != 0) {
      expr = read_binary_expr(context, new IdentifierExpression(keyword));
    } else {
      expr = read_expression(context);
    }
    if (expr != nullptr) {
      return new ExpressionStatement(expr);
    }
    return nullptr;
  }
}