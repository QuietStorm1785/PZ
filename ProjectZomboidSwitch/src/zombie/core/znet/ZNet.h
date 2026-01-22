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


class ZNet {
public:
    static const SimpleDateFormat s_logSdf = std::make_shared<SimpleDateFormat>("dd-MM-yy HH:mm:ss.SSS");

   public static native void init();

   private static native void setLogLevel(int var0);

    static void SetLogLevel(int var0) {
      DebugLog.enableLog(DebugType.Network, switch (var0) {
         case 0 -> LogSeverity.Warning;
         case 1 -> LogSeverity.General;
         case 2 -> LogSeverity.Debug;
         default -> LogSeverity.Error;
      });
   }

    static void SetLogLevel(LogSeverity var0) {
      setLogLevel(var0.ordinal());
   }

    static void logPutsCallback(const std::string& var0) {
    std::string var1 = s_logSdf.format(Calendar.getInstance().getTime());
      DebugLog.Network.print("[" + var1 + "] > " + var0);
      System.out.flush();
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
