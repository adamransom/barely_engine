//
// timer_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <thread>
#include <chrono>
#include "catch.hpp"
#include "timer.h"

using namespace BarelyEngine;

TEST_CASE("Timer", "[timer]")
{
  Timer timer;

  SECTION("Timer reports positive duration")
  {
    timer.touch();
    auto duration = timer.peek();

    REQUIRE(duration >= 0);
  }

  SECTION("Timer times correctly")
  {
    timer.touch();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto duration = timer.peek();

    REQUIRE(duration >= 1000);
    REQUIRE(duration < 2000);
  }
}
