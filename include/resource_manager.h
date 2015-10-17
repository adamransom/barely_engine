//
// resource_manager.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_RESOURCE_MANAGER_H
#define BE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>

namespace BarelyEngine {
class Texture;

/**
 * @class ResourceManager
 * @brief Manages resources used in the engine
 *
 * Assumes everything is in a folder called `resources` in the same directory as
 * the executable. Resources are then expected to be in subfolders named after
 * the type of resource:
 *  - Texture in `/textures`
 */
class ResourceManager
{
public:
  ResourceManager() {};
  ~ResourceManager();

  /**
  * @brief Loads the specified resource with type T
  *
  * @param name the file name of the resource to load
  */
  template <typename T>
  const T* load(std::string name);

  /**
   * @brief Gets the specified resource with type T
   *
   * @param name the file name of the (already loaded) resource to get
   */
  template <typename T>
  const T* get(std::string name) const;

private:
  /// Hash of textures by their names
  std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_RESOURCE_MANAGER_H)
