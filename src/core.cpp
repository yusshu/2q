/**
 * Implementations of the
 * core.h definitions
 */
#include "core.h"

//namespace qq {

  //#region Source location
  SourceLoc::SourceLoc(const char* pfilename)
    : filename(pfilename), line(0), column(0) {}

  void SourceLoc::operator++() {
    column++;
  }

  void SourceLoc::next_line() {
    line++;
    column = 0;
  }

  std::string SourceLoc::to_string() {
    std::string repr(filename);
    repr += "at line ";
    repr += line;
    repr += ", column ";
    repr += column;
    return repr;
  }
  //#endregion

//}