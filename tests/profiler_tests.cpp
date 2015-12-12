//
// profiler_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <thread>
#include "catch.hpp"
#include "frame_profiler.h"

using namespace BarelyEngine;

TEST_CASE("FrameProfiler::Scope", "[profiler]")
{
  FrameProfiler profiler;
  const char* key = "Test";

  SECTION("Adds its value to profiler after destruction")
  {
    {
      FrameProfiler::Scope{profiler, key};
    }

    REQUIRE(profiler.samples()[0].second.size() == 1);
  }

  SECTION("Times the duration of the scope")
  {
    {
      FrameProfiler::Scope scope{profiler, key};
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    auto sample = profiler.samples()[0].second.buffer()[0];

    REQUIRE(sample >= 1000);
    REQUIRE(sample < 2000);
  }
}
