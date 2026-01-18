#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZNet {
public:
 static const SimpleDateFormat s_logSdf = new SimpleDateFormat("dd-MM-yy HH:mm:ss.SSS");

 public static void init();

 private static void setLogLevel(int var0);

 static void SetLogLevel(int int0) {
 DebugLog.enableLog(DebugType.Network, switch (int0) {
 case 0 -> LogSeverity.Warning;
 case 1 -> LogSeverity.General;
 case 2 -> LogSeverity.Debug;
 default -> LogSeverity.Error;
 });
 }

 static void SetLogLevel(LogSeverity logSeverity) {
 setLogLevel(logSeverity.ordinal());
 }

 static void logPutsCallback(const std::string& string1) {
 std::string string0 = s_logSdf.format(Calendar.getInstance().getTime());
 DebugLog.Network.print("[" + string0 + "] > " + string1);
 System.out.flush();
 }
}
} // namespace znet
} // namespace core
} // namespace zombie
