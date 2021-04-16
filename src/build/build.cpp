#include <fstream>
#include "build.h"
#include "../read/streamr.h"
#include <unordered_map>
#include "../util/log.h"

void build(const std::filesystem::directory_entry& file) {
  std::ifstream input(file.path().string());
  std::unordered_map<char, int> exclusions;
  ParseContext context(input, exclusions);
  auto expr = read_statement(context);
  if (expr == nullptr) {
    info("null");
  } else {
    info(expr->repr());
  }
}