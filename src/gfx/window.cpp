//
// window.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "window.h"
#include "exception.h"

using namespace std::literals;

namespace BarelyEngine {
const int Window::kCentered = SDL_WINDOWPOS_CENTERED;

Window::Window(const std::string& title, const int width, const int height, const int x,
               const int y)
{
  // Use a try-catch here as the SDL_Window could have already been created when
  // the OpenGL context fails, so we need to clean that up!
  try
  {
    create_window(title, width, height, x, y);
    create_opengl_context();
  }
  catch (std::runtime_error& e)
  {
    if (window_ != nullptr) SDL_DestroyWindow(window_);

    throw Exception("Window could not be created! ("s + e.what() + ")");
  }
}

Window::~Window()
{
  SDL_DestroyWindow(window_);
  SDL_GL_DeleteContext(context_);
}

bool Window::set_vsync(const bool vsync)
{
  return SDL_GL_SetSwapInterval(vsync);
}

void Window::swap_buffer()
{
  SDL_GL_SwapWindow(window_);
}

//
// =============================
//        Private Methods
// =============================
//
void Window::create_window(const std::string& title, const int width, const int height, const int x,
                           const int y)
{
  window_ = SDL_CreateWindow(title.c_str(),                       // title
                             x,                                   // X position of window
                             y,                                   // Y position of window
                             width,                               // window width
                             height,                              // window height
                             SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN // flags for window
                            );

  if (window_ == nullptr)
  {
    throw std::runtime_error(SDL_GetError());
  }
}

void Window::create_opengl_context()
{
  // This engine is currently written to support OpenGL 3.3
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  // By using Core instead of the Compatibilty profile, we don't allow using
  // deprecated or removed features of OpenGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  context_ = SDL_GL_CreateContext(window_);

  if (context_ == NULL)
  {
    throw std::runtime_error(SDL_GetError());
  }
}
} // end of namespace BarelyEngine
