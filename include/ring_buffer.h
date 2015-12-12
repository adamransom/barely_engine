//
// ring_buffer.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_RING_BUFFER_H
#define BE_RING_BUFFER_H

#include <array>
#include <cassert>

namespace BarelyEngine {
/**
 * @class RingBuffer
 * @brief A partial ring buffer implementation, currently only used by the
 *        profiler (hence the partialness).
 *
 * TODO Come back and make this a proper STL container
 */
template <typename T, int S>
class RingBuffer
{
public:
  /**
   * @brief Construct a new RingBuffer
   */
  RingBuffer()
    : head_(0)
    , tail_(0)
    , empty_(true) {};

  /**
   * @brief Returns the number of elements the ring buffer can contain
   *
   * @return the number of elements the ring buffer can contain
   */
  constexpr size_t capacity() const { return S; }

  /**
   * @brief Returns the number of elements currently in the ring buffer
   *
   * @return the number of elements currently in the ring buffer
   */
  size_t size() const;

  /**
   * @brief Appends the given element value to the end of the ring buffer
   *
   * @param the element value to append to the ring buffer (copied)
   */
  void push_back(const T& value);

  /**
   * @brief Appends the given element value to the end of the ring buffer
   *
   * @param the element value to append to the ring buffer (moved)
   */
  void push_back(T&& value);

  /**
   * @brief Returns the element at the front of the ring buffer
   *
   * @return the element at the front of the ring buffer
   */
  T& front();

  /**
   * @brief Returns the element at the front of the ring buffer
   *
   * @return the element at the front of the ring buffer
   */
  const T& front() const;

  /**
   * @brief Returns the underlying array buffer (for convenience at the moment)
   *
   * @return the underlying array buffer
   */
  const std::array<T, S>& buffer() const { return buffer_; }

private:
  /**
   * @brief Update the head and tail pointers
   */
  void update_pointers();

  /// Index into the underlying array of the head of the ring buffer
  size_t head_;
  /// Index into the underlying array of the tail of the ring buffer
  size_t tail_;
  /// Whether the ring buffer is empty or not
  bool empty_;
  /// The underlying array used by the ring buffer
  std::array<T, S> buffer_;
};

template <typename T, int S>
size_t RingBuffer<T, S>::size() const
{
  if (empty_)
  {
    return 0;
  }
  else
  {
    return (tail_ > head_ ? tail_ : tail_ + S) - head_;
  }
}

template <typename T, int S>
void RingBuffer<T, S>::push_back(const T& value)
{
  buffer_[tail_] = value;
  update_pointers();
}

template <typename T, int S>
void RingBuffer<T, S>::push_back(T&& value)
{
  buffer_[tail_] = std::move(value);
  update_pointers();
}

template <typename T, int S>
T& RingBuffer<T, S>::front()
{
  assert(!empty_);
  return buffer_[head_];
}

template <typename T, int S>
const T& RingBuffer<T, S>::front() const
{
  assert(!empty_);
  return buffer_[head_];
}

//
// =============================
//        Private Methods
// =============================
//

template <typename T, int S>
void RingBuffer<T, S>::update_pointers()
{
  const auto next = (tail_ + 1) % S;

  if (empty_)
  {
    empty_ = false;
    tail_ = next;
  }
  else if (tail_ == head_)
  {
    // We are full, so wrap around, destroying the oldest value
    head_ = tail_ = next;
  }
  else
  {
    // Not full, so continue as normal
    tail_ = next;
  }
}
} // end of namespace BarelyEngine

#endif // defined(BE_RING_BUFFER_H)
