//
// basic_logger.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_BASIC_LOGGER_H
#define BE_BASIC_LOGGER_H

#include "logger.h"

namespace BarelyEngine {
/**
 * @class BasicLogger
 * @brief A basic implementation of Logger, logging the timestamp, level and
 *        message to a stream.
 */
class BasicLogger : public Logger
{
public:
  /*
   * @brief Construct a new logger for a particular stream
   *
   * @param stream the stream the logger will output to
   */
  BasicLogger(std::ostream& stream)
    : stream_(stream) {};

  /*
   * @brief Log a message
   *
   * @param level the logging level to use
   * @param message the message to log
   * @param prefix the prefix to add to the log
   */
  void log(LogLevel level, const std::string& message, const std::string& prefix = "");

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

#endif // defined(BE_BASIC_LOGGER_H)
