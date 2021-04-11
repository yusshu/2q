#include <fstream>
#include "build.h"
#include "../read/streamr.h"
#include <iostream>
#include <unordered_map>
#include "../read/expression.h"
#include "../util/log.h"

void build(const std::filesystem::directory_entry& file) {
  std::ifstream input(file.path().string());
  std::unordered_map<char, int> exclusions;
  ParseContext context(input, exclusions);
  auto expr = read_expression(context);
  info(expr->repr());
  while (true) {
    auto newExpr = read_binary_expr(context, expr);
    if (newExpr == nullptr) {
      return;
    }
    info(newExpr->repr());
    expr = newExpr;
  }
}