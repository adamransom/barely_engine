//
// logger.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include "logger.h"

namespace BarelyEngine {
/*
 * Logs a message to the stream in the format:
 *
 *    (2015-03-15 15:00) [INFO] This is a message!
 *
 */
void Logger::log(Logger::Level level, std::string message)
{
  std::string level_tag;

  switch (level)
  {
    case Level::WARN:
      level_tag = " [WARN] ";
      break;

    case Level::ERROR:
      level_tag = "[ERROR] ";
      break;

    case Level::FATAL:
      level_tag = "[FATAL] ";
      break;

    case Level::INFO:
    default:
      level_tag = " [INFO] ";
      break;
  }

  stream_ << "(" << time() << ")" << level_tag << message << std::endl;
}

void Logger::log_info(std::string message)
{
  log(Level::INFO, message);
}

void Logger::log_warn(std::string message)
{
  log(Level::WARN, message);
}

void Logger::log_error(std::string message)
{
  log(Level::ERROR, message);
}

void Logger::log_fatal(std::string message)
{
  log(Level::FATAL, message);
}

//
// =============================
//        Private Methods
// =============================
//

std::string Logger::time() const
{
  const auto time = std::time(nullptr);
  std::string time_str;
  time_str.resize(19);

  strftime(&time_str[0], time_str.size(), "%F %T", std::localtime(&time));

  return time_str;
}
} // end of namespace BarelyEngine
