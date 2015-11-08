//
// engine.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_ENGINE_H
#define BE_ENGINE_H

#include <vector>

namespace BarelyEngine {
  class Logger;
  enum class LogLevel;

/**
 * @class Engine
 * @brief Simple engine-level functionality
 */
class Engine
{
public:
  /**
   * @brief Initialises various parts of the engine including SDL
   */
  static void init();

  /**
   * @brief Registers a logger with the engine, that will be used
   *        for all log output
   *
   * @param logger the logger to register
   */
  static void register_logger(Logger* logger);

  /**
   * @brief Unregisters a logger with the engine, stopping it from being used
   *        for logging
   *
   * @param logger the logger to unregister
   */
  static void unregister_logger(Logger* logger);

  /**
   * @brief Log a message, through each registered logger. Does nothing if there
   *        are no loggers registered
   *
   * @param level the level to log at
   * @param message the message to log
   */
  static void log(LogLevel level, const std::string& message);

  /**
   * @brief Gets the list of registered loggers
   *
   * @returns a vector of registered loggers
   */
  static std::vector<Logger*> loggers() { return loggers_; }

private:
  /// The list of loggers registered with the engine
  static std::vector<Logger*> loggers_;
};
} // end of namespace BarelyEngine

#endif // defined(ENGINE_H)
