///
/// Classes for representing Project Models
///
#pragma once
#include <string>
#include <iostream>
#include <utility>

#define PM_FILE_NAME "project.qp"

struct ProjectModel {
  public:
  std::string group;
  std::string name;
  std::string version;

  ProjectModel(std::string pgroup, std::string pname, std::string pversion):
    group(std::move(pgroup)), name(std::move(pname)), version(std::move(pversion)) {}

};

///
/// Parses a project model from
/// an input stream
///
ProjectModel parse_project_model(std::istream& input);