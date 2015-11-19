//
// pixel_data.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_PIXEL_DATA_H
#define BE_PIXEL_DATA_H

#include <OpenGL/gltypes.h>

struct SDL_Surface;

namespace BarelyEngine {
/**
 * @class PixelData
 * @brief Handles preparing pixel data to be uploaded with OpenGL
 *
 * `prepare()` should be called before using `pixels()` to ensure the pixels are
 * in the correct format.
 */
class PixelData
{
public:
  /**
   * @brief Construct a new PixelData object
   *
   * @param surface the SDL_Surface to construct the PixelData from
   */
  PixelData(SDL_Surface* surface);
  ~PixelData();

  /**
   * @brief Prepare the pixel data to be uploaded
   *
   * Usually, this won't require doing anything, but occasionally it might need
   * the surface being converted to a more usuable format for uploading to the
   * GPU.
   */
  void prepare();

  /**
   * @brief Gets the pixel format in OpenGL terms
   *
   * @return a GLenum specifying the pixel format or GL_FALSE if unsupported
   */
  GLenum format() const;

  /**
   * @brief Get the raw pixel data
   *
   * @return the raw pixel data for upload to the GPU
   */
  void* pixels() const;

private:
  SDL_Surface* surface_;
  SDL_Surface* converted_surface_ = nullptr;
};
} // end of namespace BarleyEngine

#endif // defined(BE_PIXEL_DATA_H)
