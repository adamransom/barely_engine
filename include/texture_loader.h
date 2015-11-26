//
// texture_loader.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_TEXTURE_LOADER_H
#define BE_TEXTURE_LOADER_H

#include <memory>
#include <OpenGL/gltypes.h>
#include "resource_loader.h"

namespace BarelyEngine {
class Texture;
class TextureLoader;

template <>
struct LoaderOptions<TextureLoader>
{
};

/**
 * @class TextureLoader
 * @brief Handles loading textures from the file system
 */
class TextureLoader : public ResourceLoader<Texture, TextureLoader>
{
public:
  /**
   * @brief Construct a new TextureLoader
   */
  TextureLoader() {}

  /**
   * @brief Loads a texture from the file system. Assumes the files are located
   *        in `resources/textures/`
   *
   * @param filename the filename of the resource to load
   * @param options the options used to load the texture (unused)
   *
   * @return a unique_ptr to the resource
   */
  std::unique_ptr<Texture> load(const std::string& name,
                                const LoaderOptions<TextureLoader>& options) override;
};
} // end of namespace BarelyEngine

#endif // defined(BE_TEXTURE_LOADER_H)
