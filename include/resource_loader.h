//
// resource_loader.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_RESOURCE_LOADER_H
#define BE_RESOURCE_LOADER_H

#include "logging.h"

namespace BarelyEngine {
template <typename L>
struct LoaderOptions;
/**
 * @class ResourceLoader
 * @brief An abstract class that is used by resource managers to load their
 *        resources
 */
template <typename T, typename L>
class ResourceLoader
{
public:
  /**
   * @brief Loads a resource from the file system
   *
   * @param filename the filename of the resource to load
   * @param options the options used to load the resource
   *
   * @return a unique_ptr to the resource
   */
  virtual std::unique_ptr<T> load(const std::string& filename, const LoaderOptions<L>& options) = 0;

protected:
  /**
   * @brief Callback when the resource is loading (for logging)
   *
   * @param path the path of the resource
   */
  void loading(const std::string& path);

  /**
   * @brief Callback when the resource has loaded (for logging)
   *
   * @param path the path of the resource
   */
  void loaded(const std::string& path);

  /**
   * @brief Callback when the resource failed to loaded (for logging)
   *
   * @param path the path of the resource
   * @param message the reason the loading failed
   */
  void failed(const std::string& path, const std::string& message);
};

template <typename T, typename L>
void ResourceLoader<T, L>::loading(const std::string& path)
{
  BE_LOG_DEBUG("Loading resource '" + path + "'...");
}

template <typename T, typename L>
void ResourceLoader<T, L>::loaded(const std::string& path)
{
  BE_LOG("Loaded resource '" + path + "'");
}

template <typename T, typename L>
void ResourceLoader<T, L>::failed(const std::string& path, const std::string& message)
{
  BE_LOG_WARN("Failed to load resource '" + path + "' (" + message + ")");
}
} // end of namespace BarelyEngine

#endif // defined(BE_RESOURCE_LOADER_H)
