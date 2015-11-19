//
// pixel_data.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <string>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include "pixel_data.h"
#include "logging.h"
#include "exception.h"

namespace BarelyEngine {
PixelData::PixelData(SDL_Surface* surface)
  : surface_(surface)
{
  static_assert(SDL_BYTEORDER == SDL_LIL_ENDIAN, "Big endianness not supported yet!");

  if (surface == nullptr)
  {
    throw Exception("SDL_Surface cannot be null");
  }
}

void PixelData::prepare()
{
  // Only perform conversion if necessary
  if (format() == GL_FALSE)
  {
    // Convert surface to ARGB format, so that we upload to OpenGL as BGRA
    // (which is the 'optimal' upload format).
    // See: https://www.opengl.org/wiki/Common_Mistakes#Texture_upload_and_pixel_reads

    converted_surface_ = SDL_ConvertSurfaceFormat(surface_, SDL_PIXELFORMAT_ARGB8888, 0);

    if (converted_surface_ == nullptr)
    {
      BE_LOG_WARN("Texture couldn't be converted to usuable format and may appear incorrect"s +
                  SDL_GetError());
    }
  }
}

GLenum PixelData::format() const
{
  SDL_PixelFormat* pixel_format;

  if (converted_surface_ != nullptr)
  {
    pixel_format = converted_surface_->format;
  }
  else
  {
    pixel_format = surface_->format;
  }

  /**
   * In the case of 32-bit images, the pixels are stored as a 32-bit integer,
   * and since we are uploading with GL_UNSIGNED_BYTE we need to think about
   * endianness.
   *
   * TODO Look into what should happen on big-endian machines
   */
  switch (pixel_format->BitsPerPixel)
  {
    case 32:
      if (pixel_format->Rmask > pixel_format->Bmask)
      {
        if (pixel_format->Amask != 0xFF)
        {
          // SDL_PIXELFORMAT_RGB888
          // SDL_PIXELFORMAT_ARGB8888
          return GL_BGRA;
        }
      }
      else
      {
        if (pixel_format->Amask != 0xFF)
        {
          // SDL_PIXELFORMAT_BGR888
          // SDL_PIXELFORMAT_ABGR8888
          return GL_RGBA;
        }
      }

      break;

    /**
     * In the case of 24-bit images, the pixels are stored as a series of bytes,
     * each representing a particular color component. Since we use
     * GL_UNSIGNED_BYTE when uploading the texture, the SDL_PixelFormats pretty
     * much match directly with the OpenGL format.
     */
    case 24:
      if (pixel_format->Rmask < pixel_format->Bmask)
      {
        // SDL_PIXELFORMAT_RGB24
        return GL_RGB;
      }
      else
      {
        // SDL_PIXELFORMAT_BGR24
        return GL_BGR;
      }

      break;
  }

  return GL_FALSE;
}

void* PixelData::pixels() const
{
  if (converted_surface_ != nullptr)
  {
    return converted_surface_->pixels;
  }
  else
  {
    return surface_->pixels;
  }
}

PixelData::~PixelData()
{
  SDL_FreeSurface(converted_surface_);
}
} // end of namespace BarleyEngine
