/**
 * Structures for representing
 * expressions
 */
#include <string>

enum ExpressionKind {
  BINARY,
  TERNARY,
  LITERAL
};

struct Expression {

  /**
   * Tries to infer the expression
   * return type
   */
  virtual void* inferType() = 0;

  /**
   * Returns the kind of the
   * expression
   */
  virtual ExpressionKind kind() = 0;

#ifdef __2Q_DEBUG
  /**
   * Returns a string representation
   * of this expression
   */
  virtual std::string repr() = 0;
#endif

};