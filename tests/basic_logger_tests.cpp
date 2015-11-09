//
// logger_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <ostream>
#include <string>
#include "catch.hpp"
#include "basic_logger.h"

using namespace BarelyEngine;

TEST_CASE("Logging Messages", "[basic_logger]")
{
  std::ostringstream stream;
  BasicLogger logger{stream};

  logger.log(LogLevel::INFO, "Test");
  CAPTURE(stream.str());

  SECTION("Adds message to the stream")
  {
    REQUIRE(stream.str().find("Test") != std::string::npos);
  }

  SECTION("Includes a fixed length timestamp")
  {
    const auto timestamp_size = 21;
    const auto target_size = timestamp_size + std::string(" [INFO] Test\n").size();

    REQUIRE(stream.str().size() == target_size);
  }
}
