///
/// Classes for representing Project Models
///
#include <string>
#include <iostream>

#define PM_FILE_NAME "project.qp"

struct ProjectModel {
  public:
  std::string group;
  std::string name;
  std::string version;

  ProjectModel(std::string pgroup, std::string pname, std::string pversion):
    group(pgroup), name(pname), version(pversion) {}

  ProjectModel(std::istream* input) {};

};