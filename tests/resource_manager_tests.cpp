//
// resource_manager_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "catch.hpp"
#include "fakeit.hpp"
#include "resource_manager.h"

using namespace BarelyEngine;
using namespace fakeit;

/**
 * Mock Resource
 */
struct MockResource {};

TEST_CASE("Resources", "[resource_manager]")
{
  Mock<ResourceLoader<MockResource>> mock_loader;
  ResourceManager<MockResource> manager{&mock_loader.get()};

  When(Method(mock_loader, load))
    .AlwaysDo([](const std::string& name){ return std::make_unique<MockResource>(); });

  SECTION("Loading")
  {
    SECTION("Adds to resource list")
    {
      manager.load("test_resource");

      REQUIRE(manager.count() == 1);
    }

    SECTION("Calls loaders `load` method once")
    {
      manager.load("test_resource");

      Verify(Method(mock_loader, load).Using("test_resource")).Once();
    }

    SECTION("Doesn't load same resource twice")
    {
      manager.load("test_resource");
      manager.load("test_resource");

      Verify(Method(mock_loader, load)).Once();
    }

    SECTION("Returns null handle if load fails")
    {
      When(Method(mock_loader, load))
        .Do([](const std::string& name){ return nullptr; });

      auto handle = manager.load("test_resource");

      REQUIRE(handle.is_null());
    }

    SECTION("Doesn't load for empty name")
    {
      auto handle = manager.load("");

      Verify(Method(mock_loader, load)).Never();
    }

    SECTION("Returns null handle for empty name")
    {
      auto handle = manager.load("");

      REQUIRE(handle.is_null());
    }
  }

  SECTION("Reloading")
  {
    SECTION("Calls `load` for each loaded resource")
    {
      manager.load("test_resource_1");
      manager.load("test_resource_2");
      manager.reload();

      Verify(Method(mock_loader, load).Using("test_resource_1")).Twice();
      Verify(Method(mock_loader, load).Using("test_resource_2")).Twice();
    }

    SECTION("Calls `load` only for requested resource when name specified")
    {
      manager.load("test_resource_1");
      manager.load("test_resource_2");
      manager.reload("test_resource_1");

      Verify(Method(mock_loader, load).Using("test_resource_1")).Twice();
      Verify(Method(mock_loader, load).Using("test_resource_2")).Once();
    }
  }

  SECTION("Retrieving Handle")
  {
    SECTION("Gets the correct handle")
    {
      const auto loaded = manager.load("test_resource");
      const auto retrieved = manager.get("test_resource");

      REQUIRE(loaded == retrieved);
    }

    SECTION("Loads resource if not loaded yet")
    {
      manager.get("new_resource");

      Verify(Method(mock_loader, load)).Once();
    }

    SECTION("Returns null handle if load fails")
    {
      When(Method(mock_loader, load))
      .Do([](const std::string& name){ return nullptr; });

      const auto retrieved = manager.get("nope");

      REQUIRE(retrieved.is_null());
    }

    SECTION("Returns null handle for empty name")
    {
      const auto retrieved = manager.get("");

      REQUIRE(retrieved.is_null());
    }

    SECTION("Doesn't load for empty name")
    {
      auto handle = manager.get("");

      Verify(Method(mock_loader, load)).Never();
    }
  }

  SECTION("Retrieving Resource")
  {
    SECTION("Gets the resource")
    {
      auto handle = manager.load("test_resource");
      auto retrieved = manager.get(handle);

      REQUIRE(retrieved != nullptr);
    }

    SECTION("Returns null resource if null handle")
    {
      auto null_handle = Resource<MockResource>();
      auto retrieved = manager.get(null_handle);

      REQUIRE(retrieved == nullptr);
    }
  }
}