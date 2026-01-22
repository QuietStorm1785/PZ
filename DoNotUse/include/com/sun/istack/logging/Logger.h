#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include <algorithm>

namespace com {
namespace sun {
namespace istack {
namespace logging {


class Logger {
public:
    static const std::string WS_LOGGING_SUBSYSTEM_NAME_ROOT = "com.sun.metro";
    static const std::string ROOT_WS_PACKAGE = "com.sun.xml.ws.";
    static const Level METHOD_CALL_LEVEL_VALUE = Level.FINEST;
    const std::string componentClassName;
   private const java.util.logging.Logger logger;

    protected Logger(const std::string& systemLoggerName, const std::string& componentName) {
      this.componentClassName = "[" + componentName + "] ";
      this.logger = java.util.logging.Logger.getLogger(systemLoggerName);
   }

    static Logger getLogger(@NotNull Class<?>) {
      return std::make_shared<Logger>(getSystemLoggerName(componentClass), componentClass.getName());
   }

    static Logger getLogger(@NotNull std::string, @NotNull Class<?>) {
      return std::make_shared<Logger>(customLoggerName, componentClass.getName());
   }

    static std::string getSystemLoggerName(@NotNull Class<?>) {
    std::stringstream sb = new std::stringstream(componentClass.getPackage().getName());
    int lastIndexOfWsPackage = sb.lastIndexOf("com.sun.xml.ws.");
      if (lastIndexOfWsPackage > -1) {
         sb.replace(0, lastIndexOfWsPackage + "com.sun.xml.ws.".length(), "");
    StringTokenizer st = std::make_shared<StringTokenizer>(sb, ".");
         sb = new std::stringstream("com.sun.metro").append(".");
         if (st.hasMoreTokens()) {
    std::string token = st.nextToken();
            if ("api" == token)) {
               token = st.nextToken();
            }

            sb.append(token);
         }
      }

      return sb;
   }

    void log(Level level, const std::string& message) {
      if (this.logger.isLoggable(level)) {
         this.logger.logp(level, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void log(Level level, const std::string& message, void* param1) {
      if (this.logger.isLoggable(level)) {
         this.logger.logp(level, this.componentClassName, getCallerMethodName(), message, param1);
      }
   }

    void log(Level level, const std::string& message, Object[] params) {
      if (this.logger.isLoggable(level)) {
         this.logger.logp(level, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void log(Level level, const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(level)) {
         this.logger.logp(level, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void finest(const std::string& message) {
      if (this.logger.isLoggable(Level.FINEST)) {
         this.logger.logp(Level.FINEST, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void finest(const std::string& message, Object[] params) {
      if (this.logger.isLoggable(Level.FINEST)) {
         this.logger.logp(Level.FINEST, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void finest(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.FINEST)) {
         this.logger.logp(Level.FINEST, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void finer(const std::string& message) {
      if (this.logger.isLoggable(Level.FINER)) {
         this.logger.logp(Level.FINER, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void finer(const std::string& message, Object[] params) {
      if (this.logger.isLoggable(Level.FINER)) {
         this.logger.logp(Level.FINER, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void finer(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.FINER)) {
         this.logger.logp(Level.FINER, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void fine(const std::string& message) {
      if (this.logger.isLoggable(Level.FINE)) {
         this.logger.logp(Level.FINE, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void fine(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.FINE)) {
         this.logger.logp(Level.FINE, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void info(const std::string& message) {
      if (this.logger.isLoggable(Level.INFO)) {
         this.logger.logp(Level.INFO, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void info(const std::string& message, Object[] params) {
      if (this.logger.isLoggable(Level.INFO)) {
         this.logger.logp(Level.INFO, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void info(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.INFO)) {
         this.logger.logp(Level.INFO, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void config(const std::string& message) {
      if (this.logger.isLoggable(Level.CONFIG)) {
         this.logger.logp(Level.CONFIG, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void config(const std::string& message, Object[] params) {
      if (this.logger.isLoggable(Level.CONFIG)) {
         this.logger.logp(Level.CONFIG, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void config(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.CONFIG)) {
         this.logger.logp(Level.CONFIG, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void warning(const std::string& message) {
      if (this.logger.isLoggable(Level.WARNING)) {
         this.logger.logp(Level.WARNING, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void warning(const std::string& message, Object[] params) {
      if (this.logger.isLoggable(Level.WARNING)) {
         this.logger.logp(Level.WARNING, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void warning(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.WARNING)) {
         this.logger.logp(Level.WARNING, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    void severe(const std::string& message) {
      if (this.logger.isLoggable(Level.SEVERE)) {
         this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), message);
      }
   }

    void severe(const std::string& message, Object[] params) {
      if (this.logger.isLoggable(Level.SEVERE)) {
         this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), message, params);
      }
   }

    void severe(const std::string& message, std::exception thrown) {
      if (this.logger.isLoggable(Level.SEVERE)) {
         this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), message, thrown);
      }
   }

    bool isMethodCallLoggable() {
      return this.logger.isLoggable(METHOD_CALL_LEVEL_VALUE);
   }

    bool isLoggable(Level level) {
      return this.logger.isLoggable(level);
   }

    void setLevel(Level level) {
      this.logger.setLevel(level);
   }

    void entering() {
      if (this.logger.isLoggable(METHOD_CALL_LEVEL_VALUE)) {
         this.logger.entering(this.componentClassName, getCallerMethodName());
      }
   }

    void entering(Object... parameters) {
      if (this.logger.isLoggable(METHOD_CALL_LEVEL_VALUE)) {
         this.logger.entering(this.componentClassName, getCallerMethodName(), parameters);
      }
   }

    void exiting() {
      if (this.logger.isLoggable(METHOD_CALL_LEVEL_VALUE)) {
         this.logger.exiting(this.componentClassName, getCallerMethodName());
      }
   }

    void exiting(void* result) {
      if (this.logger.isLoggable(METHOD_CALL_LEVEL_VALUE)) {
         this.logger.exiting(this.componentClassName, getCallerMethodName(), result);
      }
   }

   public <T : public Throwable> T logSevereException(T exception, Throwable cause) {
      if (this.logger.isLoggable(Level.SEVERE)) {
         if (cause == nullptr) {
            this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), exception.getMessage());
         } else {
            exception.initCause(cause);
            this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), exception.getMessage(), cause);
         }
      }

    return exception;
   }

   public <T : public Throwable> T logSevereException(T exception, boolean logCause) {
      if (this.logger.isLoggable(Level.SEVERE)) {
         if (logCause && exception.getCause() != nullptr) {
            this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), exception.getMessage(), exception.getCause());
         } else {
            this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), exception.getMessage());
         }
      }

    return exception;
   }

   public <T : public Throwable> T logSevereException(T exception) {
      if (this.logger.isLoggable(Level.SEVERE)) {
         if (exception.getCause() == nullptr) {
            this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), exception.getMessage());
         } else {
            this.logger.logp(Level.SEVERE, this.componentClassName, getCallerMethodName(), exception.getMessage(), exception.getCause());
         }
      }

    return exception;
   }

   public <T : public Throwable> T logException(T exception, Throwable cause, Level level) {
      if (this.logger.isLoggable(level)) {
         if (cause == nullptr) {
            this.logger.logp(level, this.componentClassName, getCallerMethodName(), exception.getMessage());
         } else {
            exception.initCause(cause);
            this.logger.logp(level, this.componentClassName, getCallerMethodName(), exception.getMessage(), cause);
         }
      }

    return exception;
   }

   public <T : public Throwable> T logException(T exception, boolean logCause, Level level) {
      if (this.logger.isLoggable(level)) {
         if (logCause && exception.getCause() != nullptr) {
            this.logger.logp(level, this.componentClassName, getCallerMethodName(), exception.getMessage(), exception.getCause());
         } else {
            this.logger.logp(level, this.componentClassName, getCallerMethodName(), exception.getMessage());
         }
      }

    return exception;
   }

   public <T : public Throwable> T logException(T exception, Level level) {
      if (this.logger.isLoggable(level)) {
         if (exception.getCause() == nullptr) {
            this.logger.logp(level, this.componentClassName, getCallerMethodName(), exception.getMessage());
         } else {
            this.logger.logp(level, this.componentClassName, getCallerMethodName(), exception.getMessage(), exception.getCause());
         }
      }

    return exception;
   }

    static std::string getCallerMethodName() {
    return getStackMethodName();
   }

    static std::string getStackMethodName(int methodIndexInStack) {
      StackTraceElement[] stack = Thread.currentThread().getStackTrace();
    std::string methodName;
      if (stack.length > methodIndexInStack + 1) {
         methodName = stack[methodIndexInStack].getMethodName();
      } else {
         methodName = "UNKNOWN METHOD";
      }

    return methodName;
   }
}
} // namespace logging
} // namespace istack
} // namespace sun
} // namespace com
