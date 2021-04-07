#include <fstream>
#include "build.h"
#include "../read/streamr.h"
#include <iostream>
#include <unordered_map>

void build(const std::filesystem::directory_entry& file) {
  std::ifstream input(file.path().string());
  char current = (char) input.get();
  std::string test = read_identifier(&input, &current, std::unordered_map<char, int>());
  std::cout << test << std::endl;
}