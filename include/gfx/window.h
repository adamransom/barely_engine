//
// gfx/window.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_WINDOW_H
#define BE_WINDOW_H

#include <string>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace BarelyEngine {
/**
 * @class Window
 * @brief Wrapper around SDL window which also handles VSync and
 *        double-buffering
 */
class Window
{
public:
  /// Constant that can be used to specify to center the window on either axis
  static const int kCentered;

  /**
   * @brief Creates a new window
   *
   * @param title the title of the window
   * @param width the width of the window
   * @param height the height of the window
   * @param x the x position of the window (defaults to kCentered)
   * @param y the y position of the window (defaults to kCentered)
   *
   * @throws BarelyEngine::Exception if the window fails to be created
   */
  Window(const std::string& title, int width, int height, int x = kCentered, int y = kCentered);
  ~Window();

  /**
   * @brief Sets whether VSync is on or off for this window
   *
   * @param vsync whether to turn VSync on or off
   *
   * @returns true if VSync was set and false if not supported
   */
  bool set_vsync(bool vsync);

  /**
   * @brief Swaps the buffer for the double-buffered OpenGL context
   */
  void swap_buffer();

private:
  /**
   * @brief Create the SDL window
   */
  void create_window(const std::string& title, int width, int height, int x, int y);

  /**
   * @brief Create an OpenGL context
   */
  void create_opengl_context();

  /// The underlying SDL window
  SDL_Window* window_;
  /// The OpenGL context
  SDL_GLContext context_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_WINDOW_H)
