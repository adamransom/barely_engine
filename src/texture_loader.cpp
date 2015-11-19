//
// texture_loader.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <OpenGL/gl3.h>
#include "texture_loader.h"
#include "texture.h"
#include "pixel_data.h"
#include "logging.h"

using namespace std::literals;

namespace BarelyEngine {
std::unique_ptr<Texture> TextureLoader::load(const std::string& name)
{
  const auto path = "resources/textures/" + name;

  loading(path);

  const auto surface = IMG_Load(path.c_str());

  if (surface != nullptr)
  {
    BE_LOG_DEBUG("Pixel format = "s + SDL_GetPixelFormatName(surface->format->format));

    PixelData pixel_data{surface};
    pixel_data.prepare();

    auto texture =
      std::make_unique<Texture>(surface->w, surface->h, pixel_data.format(), pixel_data.pixels());
    SDL_FreeSurface(surface);
    loaded(path);

    return texture;
  }
  else
  {
    failed(path, IMG_GetError());
  }

  return nullptr;
}
} // end of namespace BarelyEngine
