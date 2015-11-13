//
// logging.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_LOGGING_H
#define BE_LOGGING_H

#include "engine.h"
#include "logger.h"

#define BE_LOG(message) Engine::log(LogLevel::INFO, message, "Engine")
#define BE_LOG_DEBUG(message) Engine::log(LogLevel::DEBUG_ONLY, message, "Engine")
#define BE_LOG_WARN(message) Engine::log(LogLevel::WARN, message, "Engine")
#define BE_LOG_ERROR(message) Engine::log(LogLevel::ERROR, message, "Engine")
#define BE_LOG_FATAL(message) Engine::log(LogLevel::FATAL, message, "Engine")

#endif // defined(BE_LOGGING_H)
