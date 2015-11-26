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
template <typename T, typename L>
class ResourceManager
{
public:
  /**
   * @struct LoadState
   * @brief Holds the state used when initially loading a resource
   *
   * It's used to reload a resource by name after loading a resource using a
   * filename and options.
   */
  struct LoadState
  {
    /// The filename for the resource
    std::string filename;
    /// The options used to load the resource
    LoaderOptions<L> options;
  };

  /**
   * @brief Construct a resource manager, creating its own loader with default
   * construction
   */
  ResourceManager()
    : loader_(std::make_shared<L>()) {};

  /**
   * @brief Construct a resource manager with a loader
   *
   * @param loader the resource loader used to load resources
   */
  ResourceManager(std::shared_ptr<L> loader)
    : loader_(std::move(loader)) {};

  /**
  * @brief Loads the specified resource with type T by filename
  *
  * @param filename the filename of the resource to load
  *
  * @return a handle to the resource requested or a null handle if the load
  *         fails
  */
  const Resource<T> load(const std::string& filename);

  /**
  * @brief Loads the specified resource with type T by filename with specific
  * options and storing the resource under the specified name
  *
  * @param filename the filename of the resource to load
  * @param name the name used to store the resource (and later reference by)
  * @param ...options the options used to load this resource
  *
  * @return a handle to the resource requested or a null handle if the load
  *         fails
  */
  template <typename... Args>
  const Resource<T> load(const std::string& filename, const std::string& name, Args... options);

  /**
   * @brief Gets the specified resource with type T
   *
   * @param name the file name of the resource to get
   *
   * @return a handle to the resource requested or a null handle if not found
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
   * @brief Reload all resources
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

  /**
   * @brief Saves the loading state for a particular resource
   *
   * @param name the name of the resource
   * @param filename the filename used to load the resource
   * @param ...options the options used to load the resource
   */
  template <typename... Args>
  void save_state(const std::string& name, const std::string& filename, Args... options);

  /// Resource loader for the manager
  std::shared_ptr<L> loader_;
  /// Hash of resources by their names
  std::unordered_map<std::string, std::unique_ptr<T>> resources_;
  /// Hash of states used to load resources initially
  std::unordered_map<std::string, LoadState> load_states_;
};

template <typename T, typename L>
const Resource<T> ResourceManager<T, L>::load(const std::string& filename)
{
  return load(filename, filename);
}

template <typename T, typename L>
template <typename... Args>
const Resource<T> ResourceManager<T, L>::load(const std::string& filename, const std::string& name,
                                              Args... options)
{
  const auto search = resources_.find(name);

  if (search != resources_.end())
  {
    return Resource<T>(name);
  }
  else
  {
    save_state(name, filename, options...);
    return force_load(name);
  }
}

template <typename T, typename L>
const Resource<T> ResourceManager<T, L>::get(const std::string& name)
{
  const auto search = resources_.find(name);

  if (search != resources_.end())
  {
    return Resource<T>(name);
  }
  else
  {
    // Null resource
    return Resource<T>();
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
template <typename T, typename L>
const T* ResourceManager<T, L>::get(const Resource<T>& resource) const
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

template <typename T, typename L>
void ResourceManager<T, L>::reload()
{
  BE_LOG("Reloading all resources...");

  for (const auto& resource : resources_)
  {
    force_load(resource.first);
  }
}

template <typename T, typename L>
void ResourceManager<T, L>::reload(const std::string& name)
{
  BE_LOG("Reloading resource '" + name + "'...");
  force_load(name);
}

//
// =============================
//        Private Methods
// =============================
//
template <typename T, typename L>
const Resource<T> ResourceManager<T, L>::force_load(const std::string& name)
{
  if (!name.empty())
  {
    const auto search = load_states_.find(name);

    if (search != load_states_.end())
    {
      auto resource = loader_->load(search->second.filename, search->second.options);

      if (resource != nullptr)
      {
        resources_[name] = std::move(resource);
        return Resource<T>(name);
      }
    }
    else
    {
      BE_LOG_WARN("Tried to load resource" + name + " without load state!");
    }
  }

  // Null resource
  return Resource<T>();
}

template <typename T, typename L>
template <typename... Args>
void ResourceManager<T, L>::save_state(const std::string& name, const std::string& filename,
                                       Args... options)
{
  load_states_[name] = {filename, LoaderOptions<L>{options...}};
}
} // end of namespace BarelyEngine

#endif // defined(BE_RESOURCE_MANAGER_H)
