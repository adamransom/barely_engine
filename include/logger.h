//
// logger.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_LOGGER_H
#define BE_LOGGER_H

#include <iostream>

namespace BarelyEngine {
/**
 * @class Logger
 * @brief Simple utility for logging to a stream
 */
class Logger
{
public:
  /**
   * @brief Various levels of log output
   */
  enum class Level
  {
    INFO,
    WARN,
    ERROR,
    FATAL
  };

  /*
   * @brief Construct a new logger for a particular stream
   *
   * @param stream the stream the logger will output to
   */
  Logger(std::ostream& stream)
    : stream_(stream) {};

  /*
   * @brief Log a message
   *
   * @param level the logging level to use
   * @param message the message to log
   */
  void log(Level level, std::string message);

  /*
   * @brief Log a message with INFO level
   *
   * @param message the message to log
   */
  void log_info(std::string message);

  /*
   * @brief Log a message with WARN level
   *
   * @param message the message to log
   */
  void log_warn(std::string message);

  /*
   * @brief Log a message with ERROR level
   *
   * @param message the message to log
   */
  void log_error(std::string message);

  /*
   * @brief Log a message with FATAL level
   *
   * @param message the message to log
   */
  void log_fatal(std::string message);

private:
  /*
   * @brief Gets the time for use in the logger output
   *
   * @returns a string representing the local time
   */
  std::string time() const;

  /// The stream this logger outputs to
  std::ostream& stream_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_LOGGER_H)
