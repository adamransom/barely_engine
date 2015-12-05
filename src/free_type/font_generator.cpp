//
// free_type/font_generator.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <algorithm>
#include <cmath>
#include <OpenGL/gl3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <ftbitmap.h>
#include "font_generator.h"
#include "library.h"
#include "face.h"
#include "bitmap.h"
#include "logging.h"
#include "font.h"
#include "texture.h"
#include "exception.h"

namespace BarelyEngine {
namespace FreeType {
FontGenerator::FontGenerator()
  : library_(std::make_unique<Library>())
{
  BE_LOG("Initialised FreeType (" + library_->version() + ")");
}

FontGenerator::~FontGenerator() = default;

std::unique_ptr<Font> FontGenerator::generate(const std::string& path, const int size)
{
  // Create face of requested font
  FreeType::Face face{*library_, path};

  // Attempt to set size. Some bitmap fonts only have specific sizes, so this may fail
  face.set_size(size);

  int texture_width = 0;
  int texture_height = 0;
  GlyphMetricsArray metrics = metrics_for_face(face, texture_width, texture_height);

  // Create empty texture using the width and height calculated above
  auto texture = std::make_unique<Texture>(texture_width,  // texture width
                                           texture_height, // texture width
                                           GL_RED,         // format of data being uploaded
                                           GL_RED,         // format to store internally
                                           1,              // unpack alignment
                                           nullptr         // no pixel data yet
                                          );

  /// The x offset of the character in the fonts texture
  int x_offset = 0;

  texture->bind();

  for (int i = 32; i < 127; i++)
  {
    face.load_glyph(i);
    FT_GlyphSlot glyph = face.glyph();

    if (glyph->format == FT_GLYPH_FORMAT_BITMAP)
    {
      Bitmap converted = convert_bitmap(glyph->bitmap);

      texture->sub_data(x_offset, 0, converted.width(), converted.rows(), converted.buffer());
    }
    else
    {
      face.render_glyph();

      texture->sub_data(x_offset, 0, glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap.buffer);
    }

    x_offset += glyph->bitmap.width;
  }

  texture->unbind();

  auto font = std::make_unique<Font>(std::move(texture), std::move(metrics));

  return font;
}

//
// =============================
//        Private Methods
// =============================
//

GlyphMetricsArray FontGenerator::metrics_for_face(Face& face, int& texture_width,
                                                  int& texture_height)
{
  GlyphMetricsArray metrics;

  // Only loop through relevant ASCII characters
  for (int i = 32; i < 127; i++)
  {
    auto glyph_metrics = metrics_for_glyph(face, i, texture_width);

    texture_width += glyph_metrics.bitmap_width;
    texture_height = std::max(texture_height, static_cast<int>(glyph_metrics.bitmap_height));

    metrics[i] = std::move(glyph_metrics);
  }

  return metrics;
}

GlyphMetrics FontGenerator::metrics_for_glyph(Face& face, const char character, const int x_offset)
{
  face.load_glyph(character, true);

  return GlyphMetrics
  {
    face.glyph()->advance.x / 64.0f, // advance_x
    face.glyph()->advance.y / 64.0f, // advance_y
    face.glyph()->bitmap.width,      // bitmap_width
    face.glyph()->bitmap.rows,       // bitmap_height
    face.glyph()->bitmap_left,       // offset_x
    face.glyph()->bitmap_top,        // offset_y
    x_offset,                        // texture_x
    0                                // texture_y
  };
}

Bitmap FontGenerator::convert_bitmap(FT_Bitmap& source)
{
  Bitmap target{library_.get()};

  // Convert source bitmap from 1-bit per pixel to 8-bits per pixel
  FT_Bitmap_Convert(library_->get(), &source, target.get(), 1);

  int size = target.pitch() * target.rows();

  // Each byte in the converted buffer is either 1 or 0; opaque or transparent.
  // We need to convert this to the 256 shades of gray OpenGL is expecting, so
  // when the byte is 1 we replace with 255 (0xFF)
  for (int i = 0; i < size; i++)
  {
    auto pixel = target.buffer()[i];

    if (pixel == 1)
    {
      target.buffer()[i] = 0xFF;
    }
  }

  return target;
}
} // end of namespace FreeType
} // end of namespace BarelyEngine
