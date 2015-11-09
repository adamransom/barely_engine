//
// engine_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "catch.hpp"
#include "fakeit.hpp"
#include "engine.h"
#include "logger.h"

using namespace BarelyEngine;
using namespace fakeit;

TEST_CASE("Engine Logging", "[engine]")
{
  Mock<Logger> mock_logger;
  Logger& logger = mock_logger.get();

  REQUIRE(Engine::loggers().size() == 0);

  SECTION("Registering a logger increases count")
  {
    Engine::register_logger(&logger);

    REQUIRE(Engine::loggers().size() == 1);
  }

  SECTION("Registering the same logger again does nothing")
  {
    Engine::register_logger(&logger);
    Engine::register_logger(&logger);

    REQUIRE(Engine::loggers().size() == 1);
  }

  SECTION("Unregistering a logger decreases count")
  {
    Engine::register_logger(&logger);
    Engine::unregister_logger(&logger);

    REQUIRE(Engine::loggers().size() == 0);
  }

  SECTION("Unregistering the same logger again does nothing")
  {
    Engine::register_logger(&logger);
    Engine::unregister_logger(&logger);
    Engine::unregister_logger(&logger);

    REQUIRE(Engine::loggers().size() == 0);
  }

  SECTION("Logging calls log method of each registered logger")
  {
    When(Method(mock_logger, log)).AlwaysReturn();

    Engine::register_logger(&logger);
    Engine::log(LogLevel::INFO, "Test");

    Verify(Method(mock_logger, log));
  }

  // Remove logger after each section as Engine is static
  Engine::unregister_logger(&logger);
}
