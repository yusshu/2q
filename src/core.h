#include <unordered_map>

// #define __2Q_PROD
namespace qq {

  /**
   * The map type used to store the
   * character exclusions, works
   * as a constant-access character
   * multi-set
   */
  using exclude_map = std::unordered_map<char, int>;

  /**
   * Represents a source location, used
   * to locate errors and log them
   */
  struct SourceLoc {
    const char* filename;
    size_t line;
    size_t column;

    SourceLoc(const char* filename);

    /** Increments the column counter */
    void operator++();

    /**
     * Increments the line counter
     * and resets the column counter
     */
    void next_line();

    /** Returns a string representation of this source loc */
    std::string to_string();

  };

}

