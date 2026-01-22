#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace logger {


class LoggerManager {
public:
    static bool s_isInitialized = false;
   private static const std::unordered_map<std::string, ZLogger> s_loggers = std::make_unique<std::unordered_map<>>();

   public static /* synchronized - TODO: add std::mutex */ ZLogger getLogger(std::string var0) {
      if (!s_loggers.containsKey(var0)) {
         createLogger(var0, false);
      }

      return s_loggers.get(var0);
   }

   public static /* synchronized - TODO: add std::mutex */ void init() {
      if (!s_isInitialized) {
         DebugLog.General.debugln("Initializing...");
         s_isInitialized = true;
         backupOldLogFiles();
      }
   }

    static void backupOldLogFiles() {
      try {
    File var0 = std::make_shared<File>(getLogsDir());
         std::string[] var1 = var0.list();
         if (var1 == nullptr || var1.length == 0) {
            return;
         }

    Calendar var3 = getLogFileLastModifiedTime(var1[0]);
    std::string var4 = "logs_";
         if (var3.get(5) < 9) {
            var4 = var4 + "0" + var3.get(5);
         } else {
            var4 = var4 + var3.get(5);
         }

         if (var3.get(2) < 9) {
            var4 = var4 + "-0" + (var3.get(2) + 1);
         } else {
            var4 = var4 + "-" + (var3.get(2) + 1);
         }

    File var2 = std::make_shared<File>(getLogsDir() + File.separator + var4);
         if (!var2.exists()) {
            var2.mkdir();
         }

         for (int var7 = 0; var7 < var1.length; var7++) {
            var4 = var1[var7];
    File var5 = std::make_shared<File>(getLogsDir() + File.separator + var4);
            if (var5.isFile()) {
               var5.renameTo(std::make_shared<File>(var2.getAbsolutePath() + File.separator + var5.getName()));
               var5.delete();
            }
         }
      } catch (Exception var6) {
         DebugLog.General.error("Exception thrown trying to initialize LoggerManager, trying to copy old log files.");
         DebugLog.General.error("Exception: ");
         DebugLog.General.error(var6);
         var6.printStackTrace();
      }
   }

    static Calendar getLogFileLastModifiedTime(const std::string& var0) {
    File var1 = std::make_shared<File>(getLogsDir() + File.separator + var0);
    Calendar var2 = Calendar.getInstance();
      var2.setTimeInMillis(var1.lastModified());
    return var2;
   }

   public static /* synchronized - TODO: add std::mutex */ void createLogger(std::string var0, boolean var1) {
      init();
      s_loggers.put(var0, std::make_shared<ZLogger>(var0, var1));
   }

    static std::string getLogsDir() {
    std::string var0 = ZomboidFileSystem.instance.getCacheDirSub("Logs");
      ZomboidFileSystem.ensureFolderExists(var0);
    File var1 = std::make_shared<File>(var0);
      return var1.getAbsolutePath();
   }

    static std::string getPlayerCoords(IsoPlayer var0) {
      return "(" + (int)var0.getX() + "," + (int)var0.getY() + "," + (int)var0.getZ() + ")";
   }
}
} // namespace logger
} // namespace core
} // namespace zombie
