//
// resource_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "catch.hpp"
#include "fakeit.hpp"
#include "resource.h"

using namespace BarelyEngine;
using namespace fakeit;

/**
 * Mock Resource
 */
struct MockResource {};

TEST_CASE("Resource", "[resource]")
{
  SECTION("Reports as null when name empty")
  {
    auto resource = Resource<MockResource>("");

    REQUIRE(resource.is_null());
  }

  SECTION("Default constructed resource is null")
  {
    auto resource = Resource<MockResource>();

    REQUIRE(resource.is_null());
  }

  SECTION("Resources with same name are equal")
  {
    auto resource_1 = Resource<MockResource>("mock_1");
    auto resource_2 = Resource<MockResource>("mock_1");

    REQUIRE(resource_1 == resource_2);
  }

  SECTION("Resources with same name are not equal")
  {
    auto resource_1 = Resource<MockResource>("mock_1");
    auto resource_2 = Resource<MockResource>("mock_2");

    REQUIRE(resource_1 != resource_2);
  }
}
