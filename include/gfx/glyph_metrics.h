//
// gfx/glyph_metrics.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_GLYPH_METRICS_H
#define BE_GLYPH_METRICS_H

#include <array>

namespace BarelyEngine {
/**
 * @struct GlyphMetrics
 * @brief Describes everything needed to render and layout a single glyph
 *
 * Only supports ASCII for now.
 */
struct GlyphMetrics
{
  /// The distance to move the cursor horizontally for the next character
  float advance_x;
  /// The distance to move the cursor vertically for the next character
  float advance_y;
  /// The width of the bitmap image
  unsigned int bitmap_width;
  /// The height of the bitmap image
  unsigned int bitmap_height;
  /// The horizontal position, relative to the cursor
  int offset_x;
  /// The vertical position, relative to the baseline
  int offset_y;
  /// The x offset in texture coordinates
  int texture_x;
  /// The y offset in texture coordinates
  int texture_y;
};

/// Convenience typedef for a collection of GlyphMetrics
using GlyphMetricsArray = std::array<GlyphMetrics, 127>;
} // end of namespace BarelyEngine

#endif // defined(BE_GLYPH_METRICS_H)
