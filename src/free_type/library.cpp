//
// library.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <ft2build.h>
#include FT_FREETYPE_H
#include <config/ftoption.h>
#include "library.h"
#include "exception.h"

namespace BarelyEngine {
namespace FreeType {
Library::Library()
{
  FT_Error error = FT_Init_FreeType(&library_);

  if (error)
  {
    throw Exception("Could not initialise FreeType [" + std::to_string(error) + "]");
  }
}

std::string Library::version() const
{
  using std::to_string;

  int major = 0;
  int minor = 0;
  int patch = 0;

  FT_Library_Version(library_, &major, &minor, &patch);

  return to_string(major) + "." + to_string(minor) + "." + to_string(patch);
}

Library::~Library()
{
  FT_Done_FreeType(library_);
}
} // end of namespace FreeType
} // end of namespace BarelyEngine
