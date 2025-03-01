#pragma once


/**
 * @file logfacade.hpp
 * @author ultr42 (ultr42.dev)
 * @brief This simple header file provides a unified logging interface for all of your logging
 * needs. Libraries use this interface to log messages, and the end-user (the executable) sets a callback to handle all log messages.
 * @version 0.1
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef LOGFACADE_HPP
#define LOGFACADE_HPP

#include "fmt/format.h"
#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace logfacade {

    enum class LogLevel { VERBOSE, DEBUG, INFO, WARN, ERR, CRITICAL };

    typedef std::function<void(LogLevel level, const std::string &name, const std::string &msg)>
        LogCallback;

    class BaseLogger {
      public:
        std::string name;
        LogCallback _callback;

        BaseLogger(const std::string &name, LogCallback callback) {
            this->name      = name;
            this->_callback = callback;
        }

        void log(LogLevel level, const std::string &msg) { _callback(level, name, msg); }
        template <typename... Args>
        void log(LogLevel level, fmt::format_string<Args...> &fmtStr, Args &&...args) {
            std::string formattedMsg = fmt::format(fmtStr, std::forward<Args>(args)...);
            this->log(level, formattedMsg);
        }
    };

    class logging {

      public:
        static inline std::optional<LogCallback> _callback;
        static void set_log_callback(LogCallback callback) { _callback = callback; }

        static BaseLogger create_logger(const std::string &name) {
            return BaseLogger(name, _callback.value());
        }
    };

#define logfacade_MAKE_LOG_LEVEL_F(level, name)                                                  \
    template <typename... Args>                                                                \
    inline void name(fmt::format_string<Args...> msg, Args &&...args) {                        \
        log(level, msg, std::forward<Args>(args)...);                                          \
    }                                                                                          \
    inline void name(const std::string &msg) { log(level, msg); }

    class Logger : public BaseLogger {
      public:
        Logger(const std::string &name) : BaseLogger(name, logging::_callback.value()) {}
        logfacade_MAKE_LOG_LEVEL_F(LogLevel::VERBOSE, verbose);
        logfacade_MAKE_LOG_LEVEL_F(LogLevel::DEBUG, debug);
        logfacade_MAKE_LOG_LEVEL_F(LogLevel::INFO, info);
        logfacade_MAKE_LOG_LEVEL_F(LogLevel::WARN, warn);
        logfacade_MAKE_LOG_LEVEL_F(LogLevel::ERR, error);
        logfacade_MAKE_LOG_LEVEL_F(LogLevel::CRITICAL, critical);
    };

} // namespace logfacade

#endif // LOGFACADE_HPP