//
// gfx/font.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FONT_H
#define BE_FONT_H

#include <string>
#include <memory>
#include "glyph_metrics.h"
#include "texture.h"

namespace BarelyEngine {
/**
 * @class Font
 * @brief A class representing how text appears on the screen.
 *
 * Only supports ASCII for the time being.
 */
class Font
{
public:
  /**
   * @brief Construct a new font
   *
   * @param texture the texture used to draw the font
   * @param metrics the glyph metrics that describe the characters in the font
   */
  Font(std::unique_ptr<Texture> texture, const GlyphMetricsArray metrics)
    : texture_(std::move(texture))
    , metrics_(std::move(metrics)) {};

  /**
   * @brief Get metrics for a particular character
   *
   * @param character the character to get the metrics for
   *
   * @return GlyphMetrics for the specified character or null if the character
   *         isn't supported
   */
  const GlyphMetrics* metrics_for_char(char character) const;

  /**
   * @brief Get the texture used to draw the font
   *
   * @return Texture containing all the glyphs for the font
   */
  Texture* texture() const { return texture_.get(); }

private:
  /// The texture used to draw the font
  std::unique_ptr<Texture> texture_;
  /// Glyph metrics for each glyph supported by the font
  GlyphMetricsArray metrics_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_FONT_H)
