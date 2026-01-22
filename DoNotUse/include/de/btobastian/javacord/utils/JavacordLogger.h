#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/slf4j/helpers/FormattingTuple.h"
#include "org/slf4j/helpers/MarkerIgnoringBase.h"
#include "org/slf4j/helpers/MessageFormatter.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class JavacordLogger : public MarkerIgnoringBase {
public:
    const std::string name;

    public JavacordLogger(const std::string& name) {
      this.name = name;
      Logger.getLogger(name).setLevel(Level.ALL);
   }

    std::string getName() {
      return this.name;
   }

    bool isTraceEnabled() {
    return false;
   }

    void trace(const std::string& msg) {
   }

    void trace(const std::string& format, void* arg) {
   }

    void trace(const std::string& format, void* arg1, void* arg2) {
   }

    void trace(const std::string& format, Object... arguments) {
   }

    void trace(const std::string& msg, std::exception t) {
   }

    bool isDebugEnabled() {
      return LoggerUtil.isDebug();
   }

    void debug(const std::string& msg) {
      if (this.isDebugEnabled()) {
    LogRecord record = std::make_shared<LogRecord>(Level.FINE, msg);
         record.setLoggerName(this.name);
         Logger.getLogger(this.name).log(record);
      }
   }

    void debug(const std::string& format, void* arg1) {
      if (this.isDebugEnabled()) {
    FormattingTuple ft = MessageFormatter.format(format, arg1);
    LogRecord record = std::make_shared<LogRecord>(Level.FINE, ft.getMessage());
         record.setThrown(ft.getThrowable());
         record.setLoggerName(this.name);
         Logger.getLogger(this.name).log(record);
      }
   }

    void debug(const std::string& format, void* arg1, void* arg2) {
      if (this.isDebugEnabled()) {
    FormattingTuple ft = MessageFormatter.format(format, arg1, arg2);
    LogRecord record = std::make_shared<LogRecord>(Level.FINE, ft.getMessage());
         record.setThrown(ft.getThrowable());
         record.setLoggerName(this.name);
         Logger.getLogger(this.name).log(record);
      }
   }

    void debug(const std::string& format, Object... arguments) {
      if (this.isDebugEnabled()) {
    FormattingTuple ft = MessageFormatter.arrayFormat(format, arguments);
    LogRecord record = std::make_shared<LogRecord>(Level.FINE, ft.getMessage());
         record.setThrown(ft.getThrowable());
         record.setLoggerName(this.name);
         Logger.getLogger(this.name).log(record);
      }
   }

    void debug(const std::string& msg, std::exception t) {
      if (this.isDebugEnabled()) {
    LogRecord record = std::make_shared<LogRecord>(Level.FINE, msg);
         record.setThrown(t);
         record.setLoggerName(this.name);
         Logger.getLogger(this.name).log(record);
      }
   }

    bool isInfoEnabled() {
    return true;
   }

    void info(const std::string& msg) {
    LogRecord record = std::make_shared<LogRecord>(Level.INFO, msg);
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void info(const std::string& format, void* arg1) {
    FormattingTuple ft = MessageFormatter.format(format, arg1);
    LogRecord record = std::make_shared<LogRecord>(Level.INFO, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void info(const std::string& format, void* arg1, void* arg2) {
    FormattingTuple ft = MessageFormatter.format(format, arg1, arg2);
    LogRecord record = std::make_shared<LogRecord>(Level.INFO, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void info(const std::string& format, Object... arguments) {
    FormattingTuple ft = MessageFormatter.arrayFormat(format, arguments);
    LogRecord record = std::make_shared<LogRecord>(Level.INFO, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void info(const std::string& msg, std::exception t) {
    LogRecord record = std::make_shared<LogRecord>(Level.INFO, msg);
      record.setThrown(t);
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    bool isWarnEnabled() {
    return true;
   }

    void warn(const std::string& msg) {
    LogRecord record = std::make_shared<LogRecord>(Level.WARNING, msg);
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void warn(const std::string& format, void* arg1) {
    FormattingTuple ft = MessageFormatter.format(format, arg1);
    LogRecord record = std::make_shared<LogRecord>(Level.WARNING, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void warn(const std::string& format, void* arg1, void* arg2) {
    FormattingTuple ft = MessageFormatter.format(format, arg1, arg2);
    LogRecord record = std::make_shared<LogRecord>(Level.WARNING, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void warn(const std::string& format, Object... arguments) {
    FormattingTuple ft = MessageFormatter.arrayFormat(format, arguments);
    LogRecord record = std::make_shared<LogRecord>(Level.WARNING, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void warn(const std::string& msg, std::exception t) {
    LogRecord record = std::make_shared<LogRecord>(Level.WARNING, msg);
      record.setThrown(t);
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    bool isErrorEnabled() {
    return true;
   }

    void error(const std::string& msg) {
    LogRecord record = std::make_shared<LogRecord>(Level.SEVERE, msg);
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void error(const std::string& format, void* arg1) {
    FormattingTuple ft = MessageFormatter.format(format, arg1);
    LogRecord record = std::make_shared<LogRecord>(Level.SEVERE, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void error(const std::string& format, void* arg1, void* arg2) {
    FormattingTuple ft = MessageFormatter.format(format, arg1, arg2);
    LogRecord record = std::make_shared<LogRecord>(Level.SEVERE, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void error(const std::string& format, Object... arguments) {
    FormattingTuple ft = MessageFormatter.arrayFormat(format, arguments);
    LogRecord record = std::make_shared<LogRecord>(Level.SEVERE, ft.getMessage());
      record.setThrown(ft.getThrowable());
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }

    void error(const std::string& msg, std::exception t) {
    LogRecord record = std::make_shared<LogRecord>(Level.SEVERE, msg);
      record.setThrown(t);
      record.setLoggerName(this.name);
      Logger.getLogger(this.name).log(record);
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
