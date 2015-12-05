//
// free_type/face.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "face.h"
#include "library.h"
#include "exception.h"
#include "logging.h"

namespace BarelyEngine {
namespace FreeType {
const int32_t Face::load_target_ = FT_LOAD_TARGET_LIGHT;

Face::Face(const Library& library, std::string path)
  : path_(std::move(path))
{
  FT_Error error = FT_New_Face(library.get(), path_.c_str(), 0, &face_);

  if (error)
  {
    throw Exception("Could not open font '" + path_ + "' [" + std::to_string(error) + "]");
  }
}

Face::~Face()
{
  FT_Done_Face(face_);
}

FT_GlyphSlot Face::glyph() const
{
  return face_->glyph;
}

void Face::set_size(int size)
{
  if (face_->num_fixed_sizes == 1)
  {
    auto height = face_->available_sizes[0].height;

    if (height != size)
    {
      BE_LOG_WARN("Specified size (" + std::to_string(size) +
                  ") for '" + path_ + "' not available. Setting only available font size (" + std::to_string(height) +
                  ")");
      size = height;
    }
  }

  auto error = FT_Set_Pixel_Sizes(face_, 0, size);

  if (error)
  {
    throw Exception("Could not set size of " + std::to_string(size) + " [" + std::to_string(error) +
                    "]");
  }
}

void Face::load_glyph(char character, bool render)
{
  int32_t flags = load_target_;

  if (render)
  {
    flags |= FT_LOAD_RENDER;
  }

  auto error = FT_Load_Char(face_, character, flags);

  if (error)
  {
    throw Exception("Could not load character '" + std::to_string(character) + "' [" +
                    std::to_string(error) + "]");
  }
}

void Face::render_glyph()
{
  auto render_mode = FT_LOAD_TARGET_MODE(load_target_);

  auto error = FT_Render_Glyph(face_->glyph, render_mode);

  if (error)
  {
    throw Exception("Could not render glyph [" + std::to_string(error) + "]");
  }
}
} // end of namespace FreeType
} // end of namespace BarelyEngine
