//
// ring_buffer_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "catch.hpp"
#include "ring_buffer.h"

using namespace BarelyEngine;

TEST_CASE("RingBuffer", "[ring_buffer]")
{
  RingBuffer<int, 5> buffer;

  SECTION("Buffer is correct capacity")
  {
    REQUIRE(buffer.capacity() == 5);
  }

  SECTION("Buffer has size 0 on initialization")
  {
    REQUIRE(buffer.size() == 0);
  }

  SECTION("Buffer has size 1 after insert")
  {
    buffer.push_back(1);

    REQUIRE(buffer.size() == 1);
  }

  SECTION("Front is correct item after 1 insert")
  {
    buffer.push_back(1);

    REQUIRE(buffer.front() == 1);
  }

  SECTION("Buffer has size 5 after full")
  {
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(6);

    REQUIRE(buffer.size() == 5);
  }


  SECTION("Front wraps around after full")
  {
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(6);

    REQUIRE(buffer.front() == 2);
  }
}
