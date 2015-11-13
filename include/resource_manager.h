//
// resource_manager.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_RESOURCE_MANAGER_H
#define BE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>
#include "resource_loader.h"
#include "resource.h"
#include "logging.h"

namespace BarelyEngine {
/**
 * @class ResourceManager
 * @brief Manages the loading and retrieving of resources via handles
 *
 * This is a very simple implementation of a resource manager, using handles
 * instead of raw pointers to resources. This means that later on it will be
 * much easier to add more sophisticated managing of resources (dedicated handle
 * manager, reference counting etc) if needed, without needing to change too
 * much client code.
 */
template <typename T>
class ResourceManager
{
public:
  /**
   * @brief Construct a resource manager
   *
   * @param loader the resource loader to be used for loading the resources
   */
  ResourceManager(ResourceLoader<T>* loader)
    : loader_(loader) {};

  /**
  * @brief Loads the specified resource with type T
  *
  * This is more of a convenience method, as its basically the reverse of the
  * `get` method. It's here just so you can specifically state you want to load
  * the resource (for pre-loading). You could pre-load with `get` also, but it's
  * not as obvious with that name (and why you aren't using the return value).
  *
  * @param name the file name of the resource to load
  *
  * @return a handle to the resource requested or a null handle if the load
  *         fails
  */
  const Resource<T> load(const std::string& name);

  /**
   * @brief Gets the specified resource with type T or loads it if not found
   *
   * @param name the file name of the resource to get
   *
   * @return a handle to the resource requested or a null handle if the load
   *         fails
   */
  const Resource<T> get(const std::string& name);

  /**
   * @brief Gets a pointer to the raw resource for the specified handle
   *
   * @param resource handle of the requested resource
   *
   * @return a pointer to the raw resource or null if it no longer exists
   */
  const T* get(const Resource<T>& resource) const;

  /**
   * @brief Reload all resources, using the ResourceLoader for each
   */
  void reload();

  /**
   * @brief Reload a specific resource
   *
   * @param name the name of the resource to reload
   */
  void reload(const std::string& name);

  /**
   * @brief Gets the number of resources currently loaded
   *
   * @return size_t of the number of resources
   */
  size_t count() const { return resources_.size(); }

private:
  /**
   * @brief Loads the resource without checking if it exists or not
   *
   * @param name the file name of the resource to load
   *
   * @return a handle to the resource requested or a null handle if the load
   *         fails
   */
  const Resource<T> force_load(const std::string& name);
  /// Resource loader for the manager
  ResourceLoader<T>* loader_;
  /// Hash of resources by their names
  std::unordered_map<std::string, std::unique_ptr<T>> resources_;
};

template <typename T>
const Resource<T> ResourceManager<T>::load(const std::string& name)
{
  return get(name);
}

template <typename T>
const Resource<T> ResourceManager<T>::get(const std::string& name)
{
  const auto search = resources_.find(name);

  if (search != resources_.end())
  {
    return Resource<T>(name);
  }
  else
  {
    return force_load(name);
  }
}

/**
 * Currently this uses a std::string as a key into an unordered_map to get the
 * actual resource pointer back from a handle. This could be made much quicker
 * by using an int for the handle key and having that as an index into an array.
 * This would most likely be done in a handle manager of some sort. TODO Add
 * this ;)
 * 
 * The function above is fine with an unordered_map as that won't be called
 * for each render frame.
 */
template <typename T>
const T* ResourceManager<T>::get(const Resource<T>& resource) const
{
  const auto search = resources_.find(resource.id());

  if (search != resources_.end())
  {
    return search->second.get();
  }
  else
  {
    return nullptr;
  }
}

template <typename T>
void ResourceManager<T>::reload()
{
  BE_LOG("Reloading all resources...");
  for (const auto& resource : resources_)
  {
    force_load(resource.first);
  }
}

template <typename T>
void ResourceManager<T>::reload(const std::string& name)
{
  BE_LOG("Reloading resource '" + name + "'...");
  force_load(name);
}

//
// =============================
//        Private Methods
// =============================
//

template <typename T>
const Resource<T> ResourceManager<T>::force_load(const std::string& name)
{
  if (!name.empty())
  {
    auto resource = loader_->load(name);

    if (resource != nullptr)
    {
      resources_[name] = std::move(resource);
      return Resource<T>(name);
    }
  }

  // Null resource
  return Resource<T>();
}
} // end of namespace BarelyEngine

#endif // defined(BE_RESOURCE_MANAGER_H)
