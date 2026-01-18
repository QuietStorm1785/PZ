#include "zombie/debug/GenericDebugLogFormatter.h"

namespace zombie {
namespace debug {

public
GenericDebugLogFormatter::GenericDebugLogFormatter(DebugType debugTypex) {
 // TODO: Implement GenericDebugLogFormatter
 return nullptr;
}

bool GenericDebugLogFormatter::isLogEnabled(LogSeverity logSeverity) {
 // TODO: Implement isLogEnabled
 return false;
}

bool GenericDebugLogFormatter::isLogSeverityEnabled(LogSeverity logSeverity) {
 // TODO: Implement isLogSeverityEnabled
 return false;
}

std::string GenericDebugLogFormatter::format(LogSeverity logSeverity,
 const std::string &string0,
 const std::string &string1,
 const std::string &string2) {
 // TODO: Implement format
 return "";
}

std::string GenericDebugLogFormatter::format(LogSeverity logSeverity,
 const std::string &string0,
 const std::string &string1,
 const std::string &string2,
 void *object) {
 // TODO: Implement format
 return "";
}

std::string GenericDebugLogFormatter::format(LogSeverity logSeverity,
 const std::string &string0,
 const std::string &string1,
 const std::string &string2,
 void *object0, void *object1) {
 // TODO: Implement format
 return "";
}

std::string GenericDebugLogFormatter::format(LogSeverity logSeverity,
 const std::string &string0,
 const std::string &string1,
 const std::string &string2,
 void *object0, void *object1,
 void *object2) {
 // TODO: Implement format
 return "";
}

} // namespace debug
} // namespace zombie
