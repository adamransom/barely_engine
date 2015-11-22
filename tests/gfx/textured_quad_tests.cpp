//
// textured_quad_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <stdint.h>
#include "catch.hpp"
#include "fakeit.hpp"
#include "textured_quad.h"

using namespace BarelyEngine;
using namespace fakeit;

// TODO Need to figure out how to test vertices with clip of texture
TEST_CASE("Vertices", "[textured_quad]")
{
  Color blue{0, 0, 255};

  SECTION("Generates correct vertices when using whole texture")
  {
    TexturedQuad tq
    {
      0,      // x
      1,      // y
      10,     // width
      20,     // height
      0,      // layer
      0,      // depth
      nullptr // texture
    };

    std::vector<float> expected_vertices = {
      0, 1, 0, 0, 0, 1, 1, 1,  // Top-Left
      10, 1, 0, 1, 0, 1, 1, 1, // Top-Right
      0, 21, 0, 0, 1, 1, 1, 1, // Bottom-Left
      10, 1, 0, 1, 0, 1, 1, 1, // Top-Right
      0, 21, 0, 0, 1, 1, 1, 1, // Bottom-Left
      10, 21, 0, 1, 1, 1, 1, 1 // Bottom-Right
    };

    REQUIRE(tq.vertices() == expected_vertices);
  }

  SECTION("Generates correct vertices when using whole texture with color")
  {
    TexturedQuad tq
    {
      0,       // x
      1,       // y
      10,      // width
      20,      // height
      0,       // layer
      0,       // depth
      nullptr, // texture
      blue     // color
    };

    std::vector<float> expected_vertices = {
      0, 1, 0, 0, 0, 0, 0, 1,  // Top-Left
      10, 1, 0, 1, 0, 0, 0, 1, // Top-Right
      0, 21, 0, 0, 1, 0, 0, 1, // Bottom-Left
      10, 1, 0, 1, 0, 0, 0, 1, // Top-Right
      0, 21, 0, 0, 1, 0, 0, 1, // Bottom-Left
      10, 21, 0, 1, 1, 0, 0, 1 // Bottom-Right
    };

    REQUIRE(tq.vertices() == expected_vertices);
  }
}
