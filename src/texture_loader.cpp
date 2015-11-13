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
#include "logging.h"

namespace BarelyEngine {
std::unique_ptr<Texture> TextureLoader::load(const std::string& name)
{
  const auto path = "resources/textures/" + name;

  loading(path);

  const auto surface = IMG_Load(path.c_str());

  if (surface != nullptr)
  {
    const auto converted_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB24, 0);
    SDL_FreeSurface(surface);

    if (converted_surface != nullptr)
    {
      auto texture = std::make_unique<Texture>(surface->w, surface->h, GL_RGB, surface->pixels);
      SDL_FreeSurface(converted_surface);
      loaded(path);

      return std::move(texture);
    }
  }
  else
  {
    failed(path, IMG_GetError());
  }

  return nullptr;
}
} // end of namespace BarelyEngine
