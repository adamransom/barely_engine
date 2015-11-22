//
// render_element_tests.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <stdint.h>
#include "catch.hpp"
#include "fakeit.hpp"
#include "render_element.h"

using namespace BarelyEngine;
using namespace fakeit;

// TODO Need to figure out how to test sorting by texture
TEST_CASE("RenderElement ID", "[render_element]")
{
  SECTION("Generates correct ID without texture")
  {
    uint8_t layer = 0b00000001;
    uint8_t depth = 0b00000011;
    uint64_t expected_id = uint64_t(0b0000000100000011) << 48;

    RenderElement r{layer, depth, {}};

    REQUIRE(r.id() == expected_id);
  }

  SECTION("Elements get compared correctly by layer")
  {
    // Elements with lowest layer get rendered first
    RenderElement re1{1, 0, {}};
    RenderElement re2{2, 0, {}};
    RenderElement re3{3, 0, {}};

    // Add in 'random' order
    std::array<RenderElement, 3> elements = {re3, re1, re2};
    std::sort(elements.begin(), elements.end());

    REQUIRE(elements[0].layer() == 1);
    REQUIRE(elements[1].layer() == 2);
    REQUIRE(elements[2].layer() == 3);
  }

  SECTION("Elements get compared correctly by depth")
  {
    // Elements with lowest depth rendered first
    RenderElement re1{0, 1, {}};
    RenderElement re2{0, 2, {}};
    RenderElement re3{0, 3, {}};

    // Add in 'random' order
    std::array<RenderElement, 3> elements = {re3, re1, re2};
    std::sort(elements.begin(), elements.end());

    REQUIRE(elements[0].depth() == 1);
    REQUIRE(elements[1].depth() == 2);
    REQUIRE(elements[2].depth() == 3);
  }

  SECTION("Elements get compared first by layer, then depth")
  {
    // Elements with lowest depth rendered first
    RenderElement re1{1, 0, {}};
    RenderElement re2{2, 1, {}};
    RenderElement re3{3, 2, {}};
    RenderElement re4{3, 1, {}};

    // Add in 'random' order
    std::array<RenderElement, 4> elements = {re3, re1, re4, re2};
    std::sort(elements.begin(), elements.end());

    REQUIRE(elements[0].layer() == 1);
    REQUIRE(elements[1].layer() == 2);
    REQUIRE(elements[2].depth() == 1);
    REQUIRE(elements[3].depth() == 2);
  }
}
