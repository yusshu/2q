#include <vector>
#include "expression.h"

#ifndef __2Q_PROD
static std::string statementKinds[] = {
    "if", "while", "expression"
};
#endif

struct Statement {

  enum Kind {
    IF, WHILE, EXPRESSION
  };

  virtual Kind kind() = 0;

#ifndef __2Q_PROD
  virtual std::string repr() = 0;
#endif
};

struct ExpressionStatement : Statement {
  Expression* expression;

  ExpressionStatement(Expression* expr) : expression(expr) {}

  Kind kind() override {
    return Kind::EXPRESSION;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    return expression->repr();
  }
#endif
};

struct ConditionalStatement : Statement {

  Kind m_kind;
  Expression* condition;
  std::vector<Statement*> body;

  ConditionalStatement(Kind kind, Expression* pcondition, std::vector<Statement*> pbody)
    : m_kind(kind), condition(pcondition), body(pbody) {}

  Kind kind() override {
    return m_kind;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    std::string repr = "[" + statementKinds[(int) m_kind] + " " + condition->repr() + " ] -> \n";
    for (Statement* statement : body) {
      if (statement == nullptr) {
        repr += "null";
      } else {
        repr += statement->repr();
      }
      repr += ";\n";
    }
    return repr;
  }
#endif

};