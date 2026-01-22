#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/areas/isoregion/IsoRegionsLogger/IsoRegionLog.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegionsLogger {
public:
   private const ConcurrentLinkedQueue<IsoRegionLog> pool = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<IsoRegionLog> loggerQueue = std::make_unique<ConcurrentLinkedQueue<>>();
    const bool consolePrint;
   private const std::vector<IsoRegionLog> logs = std::make_unique<std::vector<>>();
    const int maxLogs = 100;
    bool isDirtyUI = false;

    public IsoRegionsLogger(bool var1) {
      this.consolePrint = var1;
   }

   public std::vector<IsoRegionLog> getLogs() {
      return this.logs;
   }

    bool isDirtyUI() {
      return this.isDirtyUI;
   }

    void unsetDirtyUI() {
      this.isDirtyUI = false;
   }

    IsoRegionLog getLog() {
    IsoRegionLog var1 = this.pool.poll();
      if (var1 == nullptr) {
         var1 = std::make_unique<IsoRegionLog>();
      }

    return var1;
   }

    void log(const std::string& var1) {
      this.log(var1, nullptr);
   }

    void log(const std::string& var1, Color var2) {
      if (Core.bDebug) {
         if (this.consolePrint) {
            DebugLog.IsoRegion.println(var1);
         }

    IsoRegionLog var3 = this.getLog();
         var3.str = var1;
         var3.type = IsoRegionLogType.Normal;
         var3.col = var2;
         this.loggerQueue.offer(var3);
      }
   }

    void warn(const std::string& var1) {
      DebugLog.IsoRegion.warn(var1);
      if (Core.bDebug) {
    IsoRegionLog var2 = this.getLog();
         var2.str = var1;
         var2.type = IsoRegionLogType.Warn;
         this.loggerQueue.offer(var2);
      }
   }

    void update() {
      if (Core.bDebug) {
         for (IsoRegionLog var1 = this.loggerQueue.poll(); var1 != nullptr; var1 = this.loggerQueue.poll()) {
            if (this.logs.size() >= 100) {
    IsoRegionLog var2 = this.logs.remove(0);
               var2.col = nullptr;
               this.pool.offer(var2);
            }

            this.logs.push_back(var1);
            this.isDirtyUI = true;
         }
      }
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
