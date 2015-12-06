//
// timer.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_TIMER_H
#define BE_TIMER_H

#include <chrono>

namespace BarelyEngine {
/**
 * @class Timer
 * @brief Performs high-resolution timing
 */
class Timer
{
public:
  /// Use a steady clock so intervals can never be negative
  using clock = std::chrono::steady_clock;

  /**
   * @brief Construct a new timer
   */
  Timer()
    : then_(clock::now()) {};

  /**
   * @brief Effectively starts/resets the timer and starts counting
   */
  inline void touch() { then_ = clock::now(); }

  /*
   * @brief Returns the number of milliseconds since the timer was last touched
   *
   * @return the number of milliseconds elapsed since the last call to `touch()`
   */
  inline double peek()
  {
    std::chrono::duration<double, std::milli> elapsed = clock::now() - then_;

    return elapsed.count();
  }

private:
  /// The clock used for timing
  std::chrono::time_point<clock> then_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_TIMER_H)
