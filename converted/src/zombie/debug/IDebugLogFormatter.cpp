#include "zombie/debug/IDebugLogFormatter.h"

namespace zombie {
namespace debug {

bool IDebugLogFormatter::isLogEnabled(LogSeverity logSeverity) {
  // TODO: Implement isLogEnabled
  return false;
}

bool IDebugLogFormatter::isLogSeverityEnabled(LogSeverity logSeverity) {
  // TODO: Implement isLogSeverityEnabled
  return false;
}

std::string IDebugLogFormatter::format(LogSeverity logSeverity,
                                       const std::string &prefix,
                                       const std::string &affix,
                                       const std::string &formatNoParams) {
  // TODO: Implement format
  return "";
}

std::string IDebugLogFormatter::format(LogSeverity logSeverity,
                                       const std::string &prefix,
                                       const std::string &affix,
                                       const std::string &format,
                                       void *param0) {
  // TODO: Implement format
  return "";
}

std::string IDebugLogFormatter::format(LogSeverity logSeverity,
                                       const std::string &prefix,
                                       const std::string &affix,
                                       const std::string &format, void *param0,
                                       void *param1) {
  // TODO: Implement format
  return "";
}

std::string IDebugLogFormatter::format(LogSeverity logSeverity,
                                       const std::string &prefix,
                                       const std::string &affix,
                                       const std::string &format, void *param0,
                                       void *param1, void *param2) {
  // TODO: Implement format
  return "";
}

std::string IDebugLogFormatter::format(LogSeverity logSeverity,
                                       const std::string &prefix,
                                       const std::string &affix,
                                       const std::string &format, void *param0,
                                       void *param1, void *param2,
                                       void *param3) {
  // TODO: Implement format
  return "";
}

} // namespace debug
} // namespace zombie
