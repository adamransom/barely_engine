//
// logger.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_LOGGER_H
#define BE_LOGGER_H

#include <iostream>

namespace BarelyEngine {
/**
 * @class enum LogLevel
 * @brief Various levels of log output
 */
enum class LogLevel
{
  DEBUG_ONLY,
  INFO,
  WARN,
  ERROR,
  FATAL
};

/**
 * @class Logger
 * @brief Abstract logging interface allowing custom loggers to be registered
 *        with the engine.
 *
 *        For convenience, a BasicLogger implementation is provided within
 *        BarelyEngine.
 */
class Logger
{
public:
  /*
   * @brief Log a message
   *
   * @param level the logging level to use
   * @param message the message to log
   * @param prefix the prefix to add to the log
   */
  virtual void log(LogLevel level, const std::string& message, const std::string& prefix = "") = 0;
};
} // end of namespace BarelyEngine

#endif // defined(BE_LOGGER_H)
