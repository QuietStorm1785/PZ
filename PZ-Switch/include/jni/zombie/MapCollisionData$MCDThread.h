#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapCollisionData/PathTask.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/network/MPStatistic.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include <algorithm>

namespace zombie {


class MapCollisionData {
:
    const void* notifier;
    bool bStop;
    std::atomic boolean bSave;
    std::atomic boolean bWaiting;
    Queue<PathTask> pathTasks;

   private MapCollisionData$MCDThread(MapCollisionData var1) {
      this.this$0 = var1;
      this.notifier = std::make_unique<Object>();
      this.pathTasks = std::make_unique<ArrayDeque<>>();
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
      MPStatistic.getInstance().MapCollisionThread.Start();
      this.this$0.sync.startFrame();
      synchronized (this.this$0.renderLock) {
         for (PathTask var2 = (PathTask)this.this$0.pathTaskQueue.poll(); var2 != nullptr; var2 = (PathTask)this.this$0.pathTaskQueue.poll()) {
            var2.execute();
            var2.release();
         }

         if (this.bSave) {
            MapCollisionData.n_save();
            ZombiePopulationManager.instance.save();
            this.bSave = false;
         }

         MapCollisionData.n_update();
         ZombiePopulationManager.instance.updateThread();
      }

      this.this$0.sync.endFrame();
      MPStatistic.getInstance().MapCollisionThread.End();

      while (this.shouldWait()) {
         synchronized (this.notifier) {
            this.bWaiting = true;

            try {
               this.notifier.wait();
            } catch (InterruptedException var5) {
            }
         }
      }

      this.bWaiting = false;
   }

    bool shouldWait() {
      if (this.bStop || this.bSave) {
    return false;
      } else if (!MapCollisionData.n_shouldWait()) {
    return false;
      } else {
         return !ZombiePopulationManager.instance.shouldWait() ? false : this.this$0.pathTaskQueue.isEmpty() && this.pathTasks.isEmpty();
      }
   }
}
} // namespace zombie
