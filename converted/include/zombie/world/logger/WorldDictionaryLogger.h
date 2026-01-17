#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace world {
namespace logger {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldDictionaryLogger {
public:
private
  static final ArrayList<Log.BaseLog> _logItems =
      std::make_unique<ArrayList<>>();

  static void reset() { _logItems.clear(); }

  static void startLogging() { reset(); }

  static void log(Log.BaseLog baseLog) {
    if (!GameClient.bClient) {
      _logItems.add(baseLog);
    }
  }

  static void log(const std::string &string) { log(string, true); }

  static void log(const std::string &string, bool boolean0) {
    if (!GameClient.bClient) {
      if (boolean0) {
        DebugLog.log("WorldDictionary: " + string);
      }

      _logItems.add(new Log.Comment(string));
    }
  }

  static void saveLog(const std::string &string1) {
    if (!GameClient.bClient) {
      bool boolean0 = false;

      for (int int0 = 0; int0 < _logItems.size(); int0++) {
        Log.BaseLog baseLog0 = _logItems.get(int0);
        if (!baseLog0.isIgnoreSaveCheck()) {
          boolean0 = true;
          break;
        }
      }

      if (boolean0) {
        File file0 = new File(ZomboidFileSystem.instance.getCurrentSaveDir() +
                              File.separator);
        if (file0.exists() && file0.isDirectory()) {
          std::string string0 =
              ZomboidFileSystem.instance.getFileNameInCurrentSave(string1);
          File file1 = new File(string0);

          try(FileWriter fileWriter = new FileWriter(file1, true)) {
            fileWriter.write("log = log or {};" + System.lineSeparator());
            fileWriter.write("table.insert(log, {" + System.lineSeparator());

            for (int int1 = 0; int1 < _logItems.size(); int1++) {
              Log.BaseLog baseLog1 = _logItems.get(int1);
              baseLog1.saveAsText(fileWriter, "\t");
            }

            fileWriter.write("};" + System.lineSeparator());
          }
          catch (Exception exception) {
            exception.printStackTrace();
            throw new IOException("Error saving WorldDictionary log.");
          }
        }
      }
    }
  }
}
} // namespace logger
} // namespace world
} // namespace zombie
