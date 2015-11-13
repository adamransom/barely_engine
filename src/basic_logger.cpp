//
// logger.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include "basic_logger.h"

namespace BarelyEngine {
/*
 * Logs a message to the stream in the format:
 *
 *    (2015-03-15 15:00:00) [INFO] This is a message!
 *
 */
void BasicLogger::log(const LogLevel level, const std::string& message, const std::string& prefix)
{
  // Only show DEBUG_ONLY messages when running in debug mode
#ifndef DEBUG
  if (level == Level::DEBUG_ONLY) return;
#endif

  std::string level_tag;

  switch (level)
  {
    case LogLevel::DEBUG_ONLY:
      level_tag = "[DEBUG] ";
      break;

    case LogLevel::WARN:
      level_tag = " [WARN] ";
      break;

    case LogLevel::ERROR:
      level_tag = "[ERROR] ";
      break;

    case LogLevel::FATAL:
      level_tag = "[FATAL] ";
      break;

    case LogLevel::INFO:
    default:
      level_tag = " [INFO] ";
      break;
  }

  stream_ << "(" << time() << ")" << level_tag;

  if (!prefix.empty())
  {
    stream_ << "<" + prefix + "> ";
  }

  stream_ << message << std::endl;
}

//
// =============================
//        Private Methods
// =============================
//

std::string BasicLogger::time() const
{
  const auto time = std::time(nullptr);
  std::string time_str;
  time_str.resize(19);

  strftime(&time_str[0], time_str.size(), "%F %T", std::localtime(&time));

  return time_str;
}
} // end of namespace BarelyEngine
