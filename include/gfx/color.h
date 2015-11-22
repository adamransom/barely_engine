//
// gfx/color.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_COLOR_H
#define BE_COLOR_H

#include <cstdint>

namespace BarelyEngine {
/**
 * @class Color
 * @brief A simple container for colors
 */
class Color
{
public:
  /**
   * @brief Construct a new color, defaulting to white
   */
  Color()
    : r_(255)
    , g_(255)
    , b_(255)
    , a_(1.0f) {};

  /**
   * @brief Construct a new color
   *
   * @param r red component (0 - 255)
   * @param g red component (0 - 255)
   * @param b red component (0 - 255)
   * @param a alpha component (0.0 - 1.0)
   */
  Color(uint8_t r, uint8_t g, uint8_t b, float a = 1.0f)
    : r_(r)
    , g_(g)
    , b_(b)
    , a_(a) {};
  ~Color() {};

  /**
   * @brief Get the value of the red component
   */
  uint8_t r() const { return r_; }

  /**
   * @brief Get the value of the green component
   */
  uint8_t g() const { return g_; }

  /**
   * @brief Get the value of the blue component
   */
  uint8_t b() const { return b_; }

  /**
   * @brief Get the value of the alpha component
   */
  uint8_t a() const { return a_; }

  static const Color White;

private:
  /// The red component
  uint8_t r_;
  /// The green component
  uint8_t g_;
  /// The blue component
  uint8_t b_;
  /// The alpha component
  float a_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_COLOR_H)
