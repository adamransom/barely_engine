//
// font_loader.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FONT_LOADER_H
#define BE_FONT_LOADER_H

#include <memory>
#include "free_type/font_generator_fwd.h"
#include "resource_loader.h"

namespace BarelyEngine {
class Font;
class FontLoader;

template <>
struct LoaderOptions<FontLoader>
{
  /// Size, in pixels, of the font to load
  int size;
};

/**
 * @class FontLoader
 * @brief Handles loading fonts from the file system, using FreeType2. Most font
 *        formats should work including TTF, OTF, PCF, DFONT etc.
 */
class FontLoader : public ResourceLoader<Font, FontLoader>
{
public:
  /**
   * @brief Construct a new FontLoader
   */
  FontLoader();
  ~FontLoader();

  /**
   * @brief Loads a font from the file system. Assumes the files are located
   *        in `resources/fonts/`
   *
   * @param filename the filename of the resource to load
   * @param options the options used to load the font
   *
   * @return a unique_ptr to the resource
   */
  std::unique_ptr<Font> load(const std::string& name,
                             const LoaderOptions<FontLoader>& options) override;

private:
  // Generates fonts using FreeType2
  std::unique_ptr<FreeType::FontGenerator> font_generator_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_FONT_LOADER_H)
