//
// frame_profiler.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "frame_profiler.h"

namespace BarelyEngine {
FrameProfiler FrameProfiler::instance_;

void FrameProfiler::add_frame_sample(float dt)
{
  frame_samples_.push_back(dt);
}

void FrameProfiler::add_sample(const char* name, float value)
{
  samples_[name].push_back(value);
}
} // end of namespace BarelyEngine
