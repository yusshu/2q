/**
 * Context definitions for input
 * stream reading
 */
#pragma once
#include <istream>
#include "../core.h"
#include "expression.h"

struct ParseError : std::exception {
  const char* cause;

  ParseError(const char* pcause)
    : cause(pcause) {}

  const char* what() const noexcept override {
    return cause;
  }
};

struct ParseContext {
  std::istream& input;
  char current;
  exclude_map& exclusions;
  Expression* previous;

  ParseContext(std::istream& pinput, exclude_map& pexclusions)
    : input(pinput), exclusions(pexclusions) {
    current = pinput.get();
  }

  /**
   * Advances to the next character
   * and checks if it's a space or a
   * line break, if it is, then advances
   * again and checks.
   */
  char skip_next_spaces() {
    // Advance checking if space or break
    while (is_space_or_break(++(*this))) {};
    // Return the first non-space character
    return current;
  }

  /**
   * Similar to skip_next_spaces(), but it
   * checks if the current character is a
   * space or break.
   */
  char skip_spaces() {
    if (is_space_or_break(current)) {
      return skip_next_spaces();
    } else {
      return current;
    }
  }

  /**
   * Adds or increases the already present value
   * linked to the given key in the exclusions map
   */
  void push_exclusion(char key) {
    auto result = exclusions.find(key);
    exclusions[key] = result == exclusions.end() ? 1 : result->second + 1;
  }

  bool check_removing_exclusion(char key) {
    if (key == current) {
      auto result = exclusions.find(key);
      if (result != exclusions.end()) {
        int value = result->second - 1;
        if (value <= 0) {
          exclusions.erase(result);
        } else {
          exclusions[key] = value;
        }
        return true;
      }
    }
    return false;
  }

  bool check_exclusion(char key) {
    return exclusions.find(key) != exclusions.end();
  }

  /**
   * Asserts and removes the specified
   * key from the exclusions map, throws
   * an error if the current character isn't
   * the required key
   */
  void assert_exclusion(char key) {
    if (key == current) {
      auto result = exclusions.find(key);
      if (result == exclusions.end()) {
        throw ParseError("Unexpected token");
      } else {
        int value = result->second - 1;
        if (value <= 0) {
          exclusions.erase(result);
        } else {
          exclusions[key] = value;
        }
        skip_next_spaces();
      }
    } else {
      std::string cause = "Expected '";
      cause.push_back(key);
      cause += "' but got: '";
      cause.push_back(current);
      cause += "'";
      throw ParseError(cause.c_str());
    }
  }

  char operator++() {
    return (current = input.get());
  }
};