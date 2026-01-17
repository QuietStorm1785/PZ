#pragma once
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class IsoRegionsLogger {
public:
private
  final ConcurrentLinkedQueue<IsoRegionsLogger.IsoRegionLog> pool =
      std::make_unique<ConcurrentLinkedQueue<>>();
private
  final ConcurrentLinkedQueue<IsoRegionsLogger.IsoRegionLog> loggerQueue =
      std::make_unique<ConcurrentLinkedQueue<>>();
  const bool consolePrint;
private
  final ArrayList<IsoRegionsLogger.IsoRegionLog> logs =
      std::make_unique<ArrayList<>>();
  const int maxLogs = 100;
  bool isDirtyUI = false;

public
  IsoRegionsLogger(bool doConsolePrint) { this.consolePrint = doConsolePrint; }

public
  ArrayList<IsoRegionsLogger.IsoRegionLog> getLogs() { return this.logs; }

  bool isDirtyUI() { return this.isDirtyUI; }

  void unsetDirtyUI() { this.isDirtyUI = false; }

private
  IsoRegionsLogger.IsoRegionLog getLog() {
    IsoRegionsLogger.IsoRegionLog regionLog = this.pool.poll();
    if (regionLog == nullptr) {
      regionLog = new IsoRegionsLogger.IsoRegionLog();
    }

    return regionLog;
  }

  void log(const std::string &string) { this.log(string, nullptr); }

  void log(const std::string &string, Color color) {
    if (Core.bDebug) {
      if (this.consolePrint) {
        DebugLog.IsoRegion.println(string);
      }

      IsoRegionsLogger.IsoRegionLog regionLog = this.getLog();
      regionLog.str = string;
      regionLog.type = IsoRegionLogType.Normal;
      regionLog.col = color;
      this.loggerQueue.offer(regionLog);
    }
  }

  void warn(const std::string &string) {
    DebugLog.IsoRegion.warn(string);
    if (Core.bDebug) {
      IsoRegionsLogger.IsoRegionLog regionLog = this.getLog();
      regionLog.str = string;
      regionLog.type = IsoRegionLogType.Warn;
      this.loggerQueue.offer(regionLog);
    }
  }

  void update() {
    if (Core.bDebug) {
      for (IsoRegionsLogger.IsoRegionLog regionLog0 = this.loggerQueue.poll();
           regionLog0 != nullptr; regionLog0 = this.loggerQueue.poll()) {
        if (this.logs.size() >= 100) {
          IsoRegionsLogger.IsoRegionLog regionLog1 = this.logs.remove(0);
          regionLog1.col = nullptr;
          this.pool.offer(regionLog1);
        }

        this.logs.add(regionLog0);
        this.isDirtyUI = true;
      }
    }
  }

public
  static class IsoRegionLog {
    std::string str;
    IsoRegionLogType type;
    Color col;

    std::string getStr() { return this.str; }

    IsoRegionLogType getType() { return this.type; }

    Color getColor() {
      if (this.col != nullptr) {
        return this.col;
      } else {
        return this.type == IsoRegionLogType.Warn ? Color.red : Color.white;
      }
    }
  }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
