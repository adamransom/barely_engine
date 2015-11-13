//
// resource.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_RESOURCE_H
#define BE_RESOURCE_H

namespace BarelyEngine {
typedef std::string resource_id_t;
/**
 * @class Resource
 * @brief Lightweight resource handle, used instead of raw pointers to data
 */
template <typename T>
class Resource
{
public:
  /**
   * @brief Construct an empty (null) resource handle
   */
  Resource() {};

  /**
   * @brief Construct a resource handle for a specific resource
   *
   * Currently, the filename is used as the resource key, but this can change
   * in the future (maybe using indexes into an array of handles).
   *
   * @param name the name of the resource
   */
  Resource(const std::string& name)
    : name_(name) {};

  /**
   * @brief Checks whether this handle is empty (not pointing to a resource)
   *
   * @return a bool indicating if the resource is null or not
   */
  bool is_null() const { return name_.empty(); }

  /**
   * @brief Get the ID for this handle
   *
   * @return a resource_id_t representing the ID
   */
  resource_id_t id() const { return name_; }

  bool operator==(const Resource<T>& other) const { return id() == other.id(); }
  bool operator!=(const Resource<T>& other) const { return id() != other.id(); }

private:
  /// The name of this resource (currently used as the ID)
  std::string name_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_RESOURCE_H)
