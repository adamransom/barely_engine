//
// pixel_data_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <memory>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include "catch.hpp"
#include "fakeit.hpp"
#include "pixel_data.h"

using namespace BarelyEngine;
using namespace fakeit;

SDL_Surface* create_surface(uint32_t format)
{
  auto pixel_format = SDL_AllocFormat(format);
  auto surface =
    SDL_CreateRGBSurface(0, 0, 0, pixel_format->BitsPerPixel, pixel_format->Rmask,
                         pixel_format->Gmask, pixel_format->Bmask, pixel_format->Amask);
  SDL_FreeFormat(pixel_format);

  return surface;
}

void COMPARE_FORMAT(uint32_t sdl_format, GLenum gl_format)
{
  const auto surface = create_surface(sdl_format);
  PixelData pixel_data{surface};

  INFO("SDL_PixelFormat = " << SDL_GetPixelFormatName(sdl_format))
  REQUIRE(pixel_data.format() == gl_format);

  SDL_FreeSurface(surface);
}

TEST_CASE("PixelData", "[pixel_data]")
{
  static_assert(SDL_BYTEORDER == SDL_LIL_ENDIAN, "Big endianness not supported yet!");

  SECTION("Returns correct format for various SDL_PixelFormats")
  {
    COMPARE_FORMAT(SDL_PIXELFORMAT_RGB24, GL_RGB);
    COMPARE_FORMAT(SDL_PIXELFORMAT_BGR24, GL_BGR);
    COMPARE_FORMAT(SDL_PIXELFORMAT_RGB888, GL_BGRA);
    COMPARE_FORMAT(SDL_PIXELFORMAT_BGR888, GL_RGBA);
    COMPARE_FORMAT(SDL_PIXELFORMAT_ARGB8888, GL_BGRA);
    COMPARE_FORMAT(SDL_PIXELFORMAT_ABGR8888, GL_RGBA);
  }

  SECTION("Returns false for formats that need converting")
  {
    COMPARE_FORMAT(SDL_PIXELFORMAT_RGBA8888, GL_FALSE);
    COMPARE_FORMAT(SDL_PIXELFORMAT_BGRA8888, GL_FALSE);
  }

  SECTION("Throws exception if given null surface")
  {
    REQUIRE_THROWS(PixelData(nullptr));
  }
}
