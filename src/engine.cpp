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
std::vector<Logger*> Engine::loggers_;

void Engine::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    throw Exception("SDL could not be initialised! ("s + SDL_GetError() + ")");
  }
}

void Engine::register_logger(Logger* const logger)
{
  const auto search = std::find(loggers_.begin(), loggers_.end(), logger);

  if (search == loggers_.end())
  {
    loggers_.push_back(logger);
  }
}

void Engine::unregister_logger(Logger* const logger)
{
  loggers_.erase(std::remove(loggers_.begin(), loggers_.end(), logger), loggers_.end());
}

void Engine::log(const LogLevel level, const std::string& message)
{
  for (const auto logger : loggers_)
  {
    if (logger != nullptr)
    {
      logger->log(level, message);
    }
  }
}
} // end of namespace BarelyEngine
