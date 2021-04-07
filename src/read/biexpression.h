/**
 * Definitions for binary
 * expressions
 */
#include "expression.h"

#ifdef __2Q_DEBUG
const std::string* kindNames = {
    "indexing", "add",
    "assign_add", "subtract",
    "assign_subtract", "null_coalescing",
    "logical_or", "bitwise_or",
    "logical_and", "bitwise_and",
    "equality", "inequality",
    "less_than", "greater_than"
};
#endif

struct BinaryExpression : Expression {

  enum Kind {
    INDEXING,
    ADD, ASSIGN_ADD
    SUBTRACT, ASSIGN_SUBTRACT,
    NULL_COALESCING,
    LOGICAL_OR, BITWISE_OR,
    LOGICAL_AND, BITWISE_AND,
    EQUALITY, INEQUALITY,
    LESS_THAN, GREATER_THAN
  };

  Expression& first;
  Kind ownKind;
  Expression& second;

  BinaryExpression(const Expression& pfirst, const Expression& psecond, Kind pkind)
    : first(pfirst), second(psecond), ownKind(pkind) {}

  ExpressionKind kind() {
    return ExpressionKind::BINARY;
  }

#ifdef __2Q_DEBUG
  std::string repr() {
    return "<binary " + kindNames[(int) ownKind] + " "
      + first.repr() + " " + second.repr() + " >";
  }
#endif

};
