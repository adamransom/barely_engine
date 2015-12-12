//
// pointer_hash.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_POINTER_HASH_H
#define BE_POINTER_HASH_H

#include <vector>
#include <cassert>

namespace BarelyEngine {
/**
 * @class PointerHash
 * @brief A specific implementation of a hash table using pointers as keys
 *
 * This is a very specific hash table implementation for use in the
 * FrameProfiler class. It has been tested specifically for the following:
 * - Keys are pointers to compile-time string literals
 * - Insertions happen rarely (just one per profile line)
 * - Accesses happen much more frequently (once a frame per profile line)
 * - It needs to be simple (and quick) to iterate over every key & value
 *
 * I tried using one array of ValueEntry (which means very quick insertion and
 * access), but iterating over and testing for nullptr (to check for empty
 * entries in the array) was slow.
 *
 * It was quicker overall to use an array for storing indices into a separate
 * array of values. Insertions are a bit slower, but these happen infrequently
 * and iterating over all key/value pairs was much quicker (access were only
 * slightly slower).
 *
 * Since the keys are all pointers which are fairly close together in memory,
 * just using the address as the 'hash' and using the modulo of the capacity
 * as the index produced the least amount of collisions. Using a prime capacity
 * is important for maximum efficiency though.
 *
 * This method also allows you to set the size of the hash table larger without
 * wasting memory, since you only store as many ValueEntries as needed.
 */
template <typename P, typename T, size_t capacity>
class PointerHash
{
public:
  /**
   * @struct IndexEntry
   * @brief An entry which maps a pointer to an index into an array of values
   */
  struct IndexEntry
  {
    /// The pointer representing the key
    P ptr = nullptr;
    /// The index into the value array
    size_t index = -1;
  };

  /**
   * @struct ValueEntry
   * @brief An entry containing the pointer key and its corresponding value
   *
   * Uses naming conventions similary to the std::pair used in STL hash tables
   */
  struct ValueEntry
  {
    /// The pointer representing the key
    P first;
    /// The value corresponding to the key
    T second;

    /**
     * @brief Construct a new ValueEntry, using a default-constructed value
     *
     * @param ptr the pointer key
     */
    ValueEntry(P ptr)
      : first(ptr) {};
  };

  /**
   * @brief Construct a new PointerHash
   */
  PointerHash()
    : size_(0)
  {
    values_.reserve(capacity);
  };

  /**
   * @brief Overload of [] operator, behaving similar to std::undordered_map
   *
   * If the key is found, returns the corresponding value. If the key isn't
   * found, a new value is inserted for the key and that value is returned.
   *
   * @param ptr the pointer key to store/retrive the value of
   *
   * @return a reference to the value corresponding to the pointer key
   */
  T& operator[](P ptr)
  {
    auto index = hash(ptr) % capacity;

    // Loop through the table and look for an empty index
    do
    {
      auto& entry = indices_[index];

      if (entry.ptr == ptr)
      {
        // Found it!
        return values_[entry.index].second;
      }
      else if (entry.ptr != nullptr)
      {
        // Keep on searchin'
        index = (index + 1) % capacity;
      }
      else if (entry.ptr == nullptr)
      {
        // Empty slot, use it!
        entry.ptr = ptr;
        entry.index = size_;

        values_.emplace_back(ptr);
        return values_[size_++].second;
      }

      // Stop an infinite loop by making sure we aren't trying to add more than
      // we can handle!
      assert(size_ != capacity);
    }
    while (true);   // Keep going 'til we find a space
  }

  /**
   * @brief Returns the collection of key/value pairs for iteration
   *
   * @return an array of ValueEntry's containing the key/value pairs
   */
  const std::vector<ValueEntry>& pairs() const { return values_; }

private:
  /**
   * @brief Returns the hash of a pointer
   *
   * @return the hash of a pointer
   */
  size_t hash(P ptr) { return reinterpret_cast<size_t>(ptr); }

  /// The array of key/index pairs
  IndexEntry indices_[capacity];
  /// The array of key/value pairs
  std::vector<ValueEntry> values_;
  /// The number of key/value pairs in the hash table
  size_t size_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_POINTER_HASH_H)
