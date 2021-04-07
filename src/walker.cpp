#include "../include/walker.h"
#include "../include/log.h"
#include <dirent.h>
#include <string>

bool walkBuilding(ProjectModel* model) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir("./src")) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      std::string name = std::string(ent->d_name);
      if (name != "." && name != "..") {
        info("  > Compiling " + std::string(ent->d_name));
      } 
    }
    closedir(dir);
    return true;
  } else {
    error("\t'src' directory not found!");
    return false;
  }
}