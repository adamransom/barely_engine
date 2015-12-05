//
// free_type/library.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FREE_TYPE_LIBRARY_H
#define BE_FREE_TYPE_LIBRARY_H

#include <string>

typedef struct FT_LibraryRec_* FT_Library;

namespace BarelyEngine {
namespace FreeType {
/**
 * @brief Wrapper around FT_Library, implementing RAII
 */
class Library
{
public:
  /**
   * @brief Construct a new library object
   *
   * @throws Exception if the library fails to be constructed
   */
  Library();
  ~Library();

  /**
   * @brief Get the underlying FT_Library pointer
   *
   * @return the underlying FT_Library pointer
   */
  FT_Library get() const { return library_; }

  /**
   * @brief Get a string representation of the FreeType version
   *
   * @return a string representing the FreeType version
   */
  std::string version() const;

private:
  /// The underlying FT_Library pointer
  FT_Library library_;
};
} // end of namespace FreeType
} // end of namespace BarelyEngine

#endif // defined(BE_FREE_TYPE_LIBRARY_H)
