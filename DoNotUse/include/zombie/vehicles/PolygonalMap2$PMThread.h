#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/network/MPStatistic.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    bool bStop;
    const void* notifier;

   private PolygonalMap2$PMThread(PolygonalMap2 var1) {
      this.this$0 = var1;
      this.notifier = std::make_unique<Object>();
   }

    void run() {
      while (!this.bStop) {
         try {
            this.runInner();
         } catch (Exception var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

    void runInner() {
      MPStatistic.getInstance().PolyPathThread.Start();
      this.this$0.sync.startFrame();
      /* synchronized - TODO: add std::mutex */ (this.this$0.renderLock) {
         PolygonalMap2.instance.updateThread();
      }

      this.this$0.sync.endFrame();
      MPStatistic.getInstance().PolyPathThread.End();

      while (this.shouldWait()) {
         /* synchronized - TODO: add std::mutex */ (this.notifier) {
            try {
               this.notifier.wait();
            } catch (InterruptedException var4) {
            }
         }
      }
   }

    bool shouldWait() {
      if (this.bStop) {
    return false;
      } else if (!PolygonalMap2.instance.chunkTaskQueue.empty()) {
    return false;
      } else if (!PolygonalMap2.instance.squareTaskQueue.empty()) {
    return false;
      } else if (!PolygonalMap2.instance.vehicleTaskQueue.empty()) {
    return false;
      } else {
         return !PolygonalMap2.instance.requestTaskQueue.empty() ? false : PolygonalMap2.instance.requests.empty();
      }
   }

    void wake() {
      /* synchronized - TODO: add std::mutex */ (this.notifier) {
         this.notifier.notify();
      }
   }
}
} // namespace vehicles
} // namespace zombie
