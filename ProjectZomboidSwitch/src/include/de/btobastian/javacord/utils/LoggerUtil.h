#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/slf4j/Logger.h"
#include "org/slf4j/LoggerFactory.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class LoggerUtil {
public:
   private static volatile boolean initialized = false;
    static const void* initLock = std::make_shared<Object>();
   private static const std::unordered_map<std::string, Logger> loggers = std::make_unique<std::unordered_map<>>();
   private static volatile boolean noLogger = false;
   private static volatile boolean debug = false;

    static Logger getLogger(const std::string& name) {
      /* synchronized - TODO: add std::mutex */ (initLock) {
         if (!initialized) {
            init();
         }
      }

      if (noLogger) {
         /* synchronized - TODO: add std::mutex */ (loggers) {
    Logger logger = loggers.get(name);
            if (logger == nullptr) {
               logger = std::make_shared<JavacordLogger>(name);
               loggers.put(name, logger);
            }

    return logger;
         }
      } else {
         return LoggerFactory.getLogger(name);
      }
   }

    static Logger getLogger(Class clazz) {
    return getLogger();
   }

    static void setDebug(bool debug) {
      LoggerUtil.debug = debug;
   }

    static bool isDebug() {
    return debug;
   }

    static void init() {
      initialized = true;

      try {
         Class.forName("org.slf4j.impl.StaticLoggerBinder");
      } catch (ClassNotFoundException var1) {
         noLogger = true;
         getLogger(LoggerUtil.class).info("No SLF4J compatible logger was found. Using default javacord implementation!");
      }
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
