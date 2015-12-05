//
// font.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "font.h"

namespace BarelyEngine {
const GlyphMetrics* Font::metrics_for_char(const char character) const
{
  if (static_cast<int>(character) > 0 && static_cast<int>(character) < 128)
  {
    return &(metrics_[character]);
  }
  else
  {
    return nullptr;
  }
}
} // end of namespace BarelyEngine
