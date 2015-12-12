//
// frame_profiler.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FRAME_PROFILER_H
#define BE_FRAME_PROFILER_H

#include "pointer_hash.h"
#include "ring_buffer.h"
#include "timer.h"

namespace BarelyEngine {
/**
 * @class FrameProfiler
 * @brief Simple profiler which collects data for each frame
 *
 * TODO Allow it to work across threads
 */
class FrameProfiler
{
public:
  using SampleBuffer = RingBuffer<float, 100>;
  using SampleHash = PointerHash<const char*, SampleBuffer, 29>;

  // Forward-declare the Scope class
  class Scope;

  /**
   * @brief Construct a new FrameProfiler
   */
  FrameProfiler() {};

  /**
   * @brief Add sample to the specific frame time sample buffer
   *
   * @param dt the delta time for the frame
   */
  void add_frame_sample(float dt);

  /**
   * @brief Add a generic float sample
   *
   * @param name the name of the sample
   * @param value the float value to add
   */
  void add_sample(const char* name, float value);

  /**
   * @brief Returns the buffer of frame time samples
   *
   * @return the buffer of frame time samples
   */
  const SampleBuffer& frame_samples() const { return frame_samples_; }

  /**
   * @brief Returns the array of samples
   *
   * @return an array of pairs containing the name and matching sample buffer
   */
  const std::vector<SampleHash::ValueEntry>& samples() const { return samples_.pairs(); }

  /**
   * @brief The static instance of the FrameProfiler
   *
   * @return the instance of the FrameProfiler
   */
  static FrameProfiler& instance() { return instance_; }

private:
  /// The static instance of the FrameProfiler
  static FrameProfiler instance_;

  /// The buffer specifically for frame time samples (for FPS)
  SampleBuffer frame_samples_;
  /// The buffer for generic float samples
  SampleHash samples_;
};

/**
 * @class FrameProfiler::Scope
 * @brief Profiles a particular scope (e.g. a function)
 */
class FrameProfiler::Scope
{
public:
  /**
   * @brief Construct a new Scope
   *
   * The timer is started automatically on construction
   *
   * @param profiler the FrameProfiler to add the profile results to
   * @param name the name of the profile
   */
  Scope(FrameProfiler& profiler, const char* name)
    : profiler_(profiler)
    , name_(name) {};

  /**
   * @brief Destructor
   *
   * The duration are calculated here and then sent to the profiler
   */
  ~Scope()
  {
    auto duration = timer_.peek();
    profiler_.add_sample(name_, duration);
  };

private:
  /// The profiler used to store the results of the profile
  FrameProfiler& profiler_;
  /// The name of the profile
  const char* name_;
  /// The timer used to time the lifetime of the object
  Timer timer_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_FRAME_PROFILER_H)
