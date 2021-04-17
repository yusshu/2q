/**
 * Structures for representing
 * expressions
 */
#pragma once
#include <string>
#include <vector>

enum ExpressionKind {
  BINARY,
  TERNARY,
  FUNCTION_CALL,
  LITERAL,
  IDENTIFIER
};

struct Expression {

  /**
   * Tries to infer the expression
   * return type
   */
  virtual void* inferType() {
    return nullptr;
  }

  /**
   * Returns the kind of the
   * expression
   */
  virtual ExpressionKind kind() = 0;

#ifndef __2Q_PROD
  /**
   * Returns a string representation
   * of this expression
   */
  virtual std::string repr() = 0;
#endif

};

#ifndef __2Q_PROD
static std::string kindNames[] = {
    "indexing", "add",
    "assign_add", "subtract",
    "assign_subtract", "multiply",
    "assign_multiply", "divide", "assign_divide",
    "assign", "null_coalescing",
    "logical_or", "bitwise_or",
    "logical_and", "bitwise_and",
    "equality", "inequality",
    "less_than", "greater_than",
    "dot"
};
#endif

struct TernaryExpression : Expression {

  Expression* condition;
  Expression* truthValue;
  Expression* falseValue;

  TernaryExpression(Expression* pcondition, Expression* ptruthValue, Expression* pfalseValue)
      : condition(pcondition), truthValue(ptruthValue), falseValue(pfalseValue) {}

  ExpressionKind kind() override {
    return ExpressionKind::TERNARY;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    return "<ternary " + truthValue->repr() + " if "
           + condition->repr() + " else " + falseValue->repr() + ">";
  }
#endif

};

struct FunctionCallExpression : Expression {
  Expression* first;
  std::vector<Expression*> args;

  FunctionCallExpression(Expression* pfirst, std::vector<Expression*> pargs)
      : first(pfirst), args(pargs) {}

  ExpressionKind kind() override {
    return ExpressionKind::FUNCTION_CALL;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    std::string repr = "<call " + first->repr() + " with args (";
    for (Expression* arg : args) {
      repr += arg->repr();
      repr += ", ";
    }
    repr += ")";
    return repr;
  }
#endif
};

struct BinaryExpression : Expression {

  enum Kind {
    INDEXING,
    ADD, ASSIGN_ADD,
    SUBTRACT, ASSIGN_SUBTRACT,
    MULTIPLY, ASSIGN_MULTIPLY,
    DIVIDE, ASSIGN_DIVIDE,
    ASSIGN,
    NULL_COALESCING,
    LOGICAL_OR, BITWISE_OR,
    LOGICAL_AND, BITWISE_AND,
    EQUALITY, INEQUALITY,
    LESS_THAN, GREATER_THAN,
    DOT
  };

  Expression* first;
  Kind ownKind;
  Expression* second;

  BinaryExpression(Expression* pfirst, Expression* psecond, Kind pkind)
      : first(pfirst), second(psecond), ownKind(pkind) {}

  ExpressionKind kind() override {
    return ExpressionKind::BINARY;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    return "<" + kindNames[(int) ownKind] + " "
           + first->repr() + " " + second->repr() + ">";
  }
#endif

};

template <class T>
struct LiteralExpression : Expression {

  T value;

  explicit LiteralExpression(T pvalue) : value(pvalue) {}

  ExpressionKind kind() override {
    return ExpressionKind::LITERAL;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    return "<literal " + std::to_string(value) + ">";
  }
#endif

};

struct IdentifierExpression : Expression {

  std::string name;

  explicit IdentifierExpression(std::string pname) : name(pname) {}

  ExpressionKind kind() override {
    return ExpressionKind::IDENTIFIER;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    return "<identifier " + name + ">";
  }
#endif

};

template<>
struct LiteralExpression<std::string> : Expression {

  std::string value;

  explicit LiteralExpression(std::string pvalue) : value(pvalue) {}

  ExpressionKind kind() override {
    return ExpressionKind::LITERAL;
  }

#ifndef __2Q_PROD
  std::string repr() override {
    return "<literal '" + value + "'>";
  }
#endif

};