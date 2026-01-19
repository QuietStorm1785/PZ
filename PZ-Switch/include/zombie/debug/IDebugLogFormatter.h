#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IDebugLogFormatter {
public:
 virtual ~IDebugLogFormatter() = default;
 bool isLogEnabled(LogSeverity logSeverity);

 bool isLogSeverityEnabled(LogSeverity logSeverity);

 std::string format(LogSeverity logSeverity, std::string_view prefix,
 std::string_view affix,
 std::string_view formatNoParams);

 std::string format(LogSeverity logSeverity, std::string_view prefix,
 std::string_view affix, std::string_view format,
 void *param0);

 std::string format(LogSeverity logSeverity, std::string_view prefix,
 std::string_view affix, std::string_view format,
 void *param0, void *param1);

 std::string format(LogSeverity logSeverity, std::string_view prefix,
 std::string_view affix, std::string_view format,
 void *param0, void *param1, void *param2);

 std::string format(LogSeverity logSeverity, std::string_view prefix,
 std::string_view affix, std::string_view format,
 void *param0, void *param1, void *param2, void *param3);

 String format(LogSeverity logSeverity, String prefix, String affix,
 String format, Object param0, Object param1, Object param2,
 Object param3, Object param4);

 String format(LogSeverity logSeverity, String prefix, String affix,
 String format, Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5);

 String format(LogSeverity logSeverity, String prefix, String affix,
 String format, Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5, Object param6);

 String format(LogSeverity logSeverity, String prefix, String affix,
 String format, Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5, Object param6,
 Object param7);

 String format(LogSeverity logSeverity, String prefix, String affix,
 String format, Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5, Object param6,
 Object param7, Object param8);
}
} // namespace debug
} // namespace zombie
