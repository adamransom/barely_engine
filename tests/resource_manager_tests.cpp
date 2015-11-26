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
 * Mock Resource, Loader and Options
 */
struct MockResource {};
class MockResourceLoader : public ResourceLoader<MockResource, MockResourceLoader> {};
template<> struct LoaderOptions<MockResourceLoader> { int size; };
using MockLoaderOptions = LoaderOptions<MockResourceLoader>;

/// Used for FakeIt argument matchers, to make sure we are passing the correct
/// options to the loader
bool operator==(const MockLoaderOptions& a, const MockLoaderOptions& b) { return a.size == b.size; }
/// Used to make sure the shared pointer doesn't delete the ResourceLoader
struct do_not_delete { void operator()(MockResourceLoader* p) const { } };

TEST_CASE("Resources", "[resource_manager]")
{
  Mock<MockResourceLoader> mock_loader;
  // It's safe (and necessary) for the shared pointer NOT to do the deleting,
  // because we know the Mock is managing the lifetime of the ResourceLoader.
  std::shared_ptr<MockResourceLoader> mock_ptr{ &mock_loader.get(), do_not_delete() };
  ResourceManager<MockResource, MockResourceLoader> manager{mock_ptr};

  When(Method(mock_loader, load))
    .AlwaysDo([](const std::string& filename, const LoaderOptions<MockResourceLoader>& options){
      return std::make_unique<MockResource>();
    });

  SECTION("Loading")
  {
    SECTION("Args: filename")
    {
      SECTION("Adds to resource list")
      {
        manager.load("test_resource");

        REQUIRE(manager.count() == 1);
      }

      SECTION("Calls loaders `load` method once")
      {
        manager.load("test_resource");

        Verify(Method(mock_loader, load).Using("test_resource", _)).Once();
      }

      SECTION("Doesn't load same resource twice")
      {
        manager.load("test_resource");
        manager.load("test_resource");

        Verify(Method(mock_loader, load)).Once();
      }

      SECTION("Returns valid handle")
      {
        auto handle = manager.load("test_resource");

        REQUIRE(handle.is_null() == false);
      }

      SECTION("Returns null handle if load fails")
      {
        When(Method(mock_loader, load))
          .Do([](const std::string& name, const MockLoaderOptions& options){ return nullptr; });

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

    SECTION("Args: filename, name")
    {
      SECTION("Calls loaders `load` with filename, not name, once")
      {
        manager.load("test_resource", "test_name");

        Verify(Method(mock_loader, load).Using("test_resource", _)).Once();
      }
    }

    SECTION("Args: filename, name, options...")
    {
      SECTION("Calls loaders `load` with LoaderOptions filled")
      {
        manager.load("test_resource", "test_name", 1);

        Verify(Method(mock_loader, load).Using("test_resource", MockLoaderOptions{1})).Once();
      }
    }
  }

  SECTION("Reloading")
  {
    SECTION("Load args: filename")
    {
      SECTION("Calls `load` for each resource")
      {
        manager.load("test_resource_1");
        manager.load("test_resource_2");
        manager.reload();

        Verify(Method(mock_loader, load).Using("test_resource_1", _)).Twice();
        Verify(Method(mock_loader, load).Using("test_resource_2", _)).Twice();
      }

      SECTION("Calls `load` only for requested resource when name specified")
      {
        manager.load("test_resource_1");
        manager.load("test_resource_2");
        manager.reload("test_resource_1");

        Verify(Method(mock_loader, load).Using("test_resource_1", _)).Twice();
        Verify(Method(mock_loader, load).Using("test_resource_2", _)).Once();
      }
    }

    SECTION("Load args: filename, name")
    {
      SECTION("Calls `load` for each resource with original filename")
      {
        manager.load("test_resource_1", "test_name_1");
        manager.load("test_resource_2", "test_name_2");
        manager.reload();

        Verify(Method(mock_loader, load).Using("test_resource_1", _)).Twice();
        Verify(Method(mock_loader, load).Using("test_resource_2", _)).Twice();
      }

      SECTION("Calls `load` for requested resource with original filename")
      {
        manager.load("test_resource", "test_name");
        manager.reload("test_name");

        Verify(Method(mock_loader, load).Using("test_resource", _)).Twice();
      }
    }

    SECTION("Load args: filename, name, options...")
    {
      SECTION("Calls `load` for each resource with original filename and options")
      {
        manager.load("test_resource_1", "test_name_1", 1);
        manager.load("test_resource_2", "test_name_2", 2);
        manager.reload();

        Verify(Method(mock_loader, load).Using("test_resource_1", MockLoaderOptions{1})).Twice();
        Verify(Method(mock_loader, load).Using("test_resource_2", MockLoaderOptions{2})).Twice();
      }

      SECTION("Calls `load` for requested resource with original filename and options")
      {
        manager.load("test_resource", "test_name", 1);
        manager.reload("test_name");

        Verify(Method(mock_loader, load).Using("test_resource", MockLoaderOptions{1})).Twice();
      }
    }
  }

  SECTION("Retrieving Handle")
  {
    SECTION("Load args: filename")
    {
      SECTION("Gets the correct handle")
      {
        const auto loaded = manager.load("test_resource");
        const auto retrieved = manager.get("test_resource");

        REQUIRE(loaded == retrieved);
      }

      SECTION("Returns null handle if not loaded")
      {
        const auto retrieved = manager.get("nope");

        REQUIRE(retrieved.is_null());
      }
    }

    SECTION("Load args: filename, name")
    {
      SECTION("Gets the correct handle based on name, not filename")
      {
        const auto loaded = manager.load("test_resource", "test_name");
        const auto retrieved = manager.get("test_name");

        REQUIRE(loaded == retrieved);
      }
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
