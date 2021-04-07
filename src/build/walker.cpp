#include <filesystem>
#include "../util/log.h"
#include "walker.h"
#include "build.h"

void walkBuilding(ProjectModel* model) {
  if (!std::filesystem::exists("src")) {
    error("  < 'src' directory not found");
    return;
  }
  for (const auto& child : std::filesystem::recursive_directory_iterator("src")) {
    if (!child.is_directory()) {
      info("  > Building " + child.path().string());
      build(child);
    }
  }
}