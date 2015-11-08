//
// logging.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef LOGGING_H
#define LOGGING_H

#include "engine.h"
#include "logger.h"

#define LOG(message) Engine::log(LogLevel::INFO, message)
#define LOG_DEBUG(message) Engine::log(LogLevel::DEBUG_ONLY, message)
#define LOG_WARN(message) Engine::log(LogLevel::WARN, message)
#define LOG_ERROR(message) Engine::log(LogLevel::ERROR, message)
#define LOG_FATAL(message) Engine::log(LogLevel::FATAL, message)

#endif // defined(LOGGING_H)
