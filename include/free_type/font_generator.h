//
// free_type/font_generator.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FREE_TYPE_FONT_GENERATOR_H
#define BE_FREE_TYPE_FONT_GENERATOR_H

#include <memory>
#include <string>
#include "glyph_metrics.h"
#include "bitmap.h"

typedef struct FT_Bitmap_ FT_Bitmap;

namespace BarelyEngine {
class Font;
namespace FreeType {
class Library;
class Face;

/**
 * @brief Uses FreeType to generate bitmap fonts from various formats
 */
class FontGenerator
{
public:
  /**
   * @brief Constructs a new FontGenerator object
   */
  FontGenerator();
  ~FontGenerator();

  /**
   * @brief Generate a Font using FreeType2
   *
   * @param path the path of the font to load
   * @param size the size to load
   *
   * @return a unique pointer to the generated font
   */
  std::unique_ptr<Font> generate(const std::string& path, int size);

private:
  /**
   * @brief Create an array of GlyphMetrics for the specified font
   *
   * @param face the FreeType font face to generate metrics for
   * @param texture_width address of int to fill with the final texture width
   * @param texture_height address of int to fill with the final texture height
   *
   * @return a GlyphMetricsArray of all ASCII glyphs in the font
   */
  GlyphMetricsArray metrics_for_face(Face& face, int& texture_width, int& texture_height);

  /**
   * @brief Get the GlyphMetrics for a specific character in a font
   *
   * @param face the font face containing the character
   * @param character the character to get the metrics for
   * @param x_offset the x offset into the texture of the font
   *
   * @return the GlyphMetrics for a particular character
   */
  GlyphMetrics metrics_for_glyph(Face& face, char character, int x_offset);

  /**
   * @brief Convert a 1-bit per pixel bitmap to an 8-bits per pixel bitmap,
   *        ready for upload to OpenGL
   *
   * @param source the 1-bit per pixel bitmap to convert
   *
   * @return the converted 8-bits per pixel bitmap
   */
  Bitmap convert_bitmap(FT_Bitmap& source);

  /// The library used for font generation
  std::unique_ptr<Library> library_;
};
} // end of namespace FreeType
} // end of namespace BarelyEngine

#endif // defined(BE_FREE_TYPE_FONT_GENERATOR_H)
