//
// resource_manager.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <SDL2/SDL_image.h>
#include "resource_manager.h"
#include "texture.h"

namespace BarelyEngine {
template <>
const Texture* ResourceManager::get(std::string name) const
{
  const auto search = textures_.find(name);

  if (search != textures_.end())
  {
    return search->second.get();
  }
  else
  {
    return nullptr;
  }
}

/*
 * Loads a texture. Returns the texture immediately if it has already been
 * loaded.
 *
 * Assumes textures are located in `resources/textures` and currently only
 * supports .bmp files.
 */
template <>
const Texture* ResourceManager::load(std::string name)
{
  const auto texture = get<Texture>(name);

  if (texture != nullptr)
  {
    return texture;
  }
  else
  {
    const auto path = "resources/textures/" + name + ".bmp";
    const auto surface = IMG_Load(path.c_str());

    if (surface != nullptr)
    {
      auto texture = std::make_unique<Texture>(surface->w, surface->h, surface->pixels);
      SDL_FreeSurface(surface);

      textures_[name] = std::move(texture);

      return textures_[name].get();
    }
    else
    {
      return nullptr;
    }
  }
}

/*
 * Need an empty destructor here so the unique_ptr to the forward-declared
 * Gfx::Texture can be deleted safely
 */
ResourceManager::~ResourceManager()
{
}
} // end of namespace BarelyEngine
