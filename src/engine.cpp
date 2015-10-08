//
// engine.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include <SDL2/SDL.h>
#include "engine.h"
#include "exception.h"
#include "logger.h"

using namespace std::literals;

namespace BarelyEngine {
void Engine::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    throw Exception("SDL could not be initialised! ("s + SDL_GetError() + ")");
  }
}
} // end of namespace BarelyEngine
