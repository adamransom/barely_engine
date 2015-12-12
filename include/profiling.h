//
// profiling.h
// Copyright (c) 2015 Adam Ransom
//

#include "frame_profiler.h"

/// Token-pasting helpers for create unique variable names
#define SCOPE_VARIABLE(line) scope_##line
#define CREATE_SCOPE(name, line) BarelyEngine::FrameProfiler::Scope SCOPE_VARIABLE(line){BarelyEngine::FrameProfiler::instance(), name};
/// Time a particular scope
#define PROFILE_SCOPE(name) CREATE_SCOPE(name, __LINE__)
/// Sample a generic value
#define PROFILE_VALUE(name, value) BarelyEngine::FrameProfiler::instance().add_sample(name, value);
/// Sample a frame's delta time
#define PROFILE_FRAME(dt) BarelyEngine::FrameProfiler::instance().add_frame_sample(dt);
