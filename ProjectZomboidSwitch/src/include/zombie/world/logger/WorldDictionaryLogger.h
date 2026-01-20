#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/world/logger/Log/BaseLog.h"
#include "zombie/world/logger/Log/Comment.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
namespace logger {


class WorldDictionaryLogger {
public:
   private static const std::vector<BaseLog> _logItems = std::make_unique<std::vector<>>();

    static void reset() {
      _logItems.clear();
   }

    static void startLogging() {
      reset();
   }

    static void log(BaseLog var0) {
      if (!GameClient.bClient) {
         _logItems.push_back(var0);
      }
   }

    static void log(const std::string& var0) {
      log(var0, true);
   }

    static void log(const std::string& var0, bool var1) {
      if (!GameClient.bClient) {
         if (var1) {
            DebugLog.log("WorldDictionary: " + var0);
         }

         _logItems.push_back(std::make_shared<Comment>(var0));
      }
   }

    static void saveLog(const std::string& var0) {
      if (!GameClient.bClient) {
    bool var1 = false;

         for (int var3 = 0; var3 < _logItems.size(); var3++) {
    BaseLog var2 = _logItems.get(var3);
            if (!var2.isIgnoreSaveCheck()) {
               var1 = true;
               break;
            }
         }

         if (var1) {
    File var13 = std::make_shared<File>(ZomboidFileSystem.instance.getCurrentSaveDir() + File.separator);
            if (var13.exists() && var13.isDirectory()) {
    std::string var4 = ZomboidFileSystem.instance.getFileNameInCurrentSave(var0);
    File var5 = std::make_shared<File>(var4);

               try (FileWriter var6 = std::make_shared<FileWriter>(var5, true)) {
                  var6.write("log = log or {};" + System.lineSeparator());
                  var6.write("table.insert(log, {" + System.lineSeparator());

                  for (int var7 = 0; var7 < _logItems.size(); var7++) {
    BaseLog var12 = _logItems.get(var7);
                     var12.saveAsText(var6, "\t");
                  }

                  var6.write("};" + System.lineSeparator());
               } catch (Exception var11) {
                  var11.printStackTrace();
                  throw IOException("Error saving WorldDictionary log.");
               }
            }
         }
      }
   }
}
} // namespace logger
} // namespace world
} // namespace zombie
