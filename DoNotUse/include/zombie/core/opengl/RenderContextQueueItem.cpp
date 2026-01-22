#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace opengl {


class RenderContextQueueItem {
public:
    Runnable m_runnable;
    bool m_isFinished;
    bool m_isWaiting;
    std::exception m_runnableThrown = nullptr;
    const void* m_waitLock = "RenderContextQueueItem Wait Lock";

    private RenderContextQueueItem() {
   }

    static RenderContextQueueItem alloc(Runnable var0) {
    RenderContextQueueItem var1 = std::make_shared<RenderContextQueueItem>();
      var1.resetInternal();
      var1.m_runnable = var0;
    return var1;
   }

    void resetInternal() {
      this.m_runnable = nullptr;
      this.m_isFinished = false;
      this.m_runnableThrown = nullptr;
   }

    void waitUntilFinished(BooleanSupplier var1) {
      while (!this.isFinished()) {
         if (!var1.getAsBoolean()) {
            return;
         }

         /* synchronized - TODO: add std::mutex */ (this.m_waitLock) {
            if (!this.isFinished()) {
               this.m_waitLock.wait();
            }
         }
      }
   }

    bool isFinished() {
      return this.m_isFinished;
   }

    void setWaiting() {
      this.m_isWaiting = true;
   }

    bool isWaiting() {
      return this.m_isWaiting;
   }

    void invoke() {
      try {
         this.m_runnableThrown = nullptr;
         this.m_runnable.run();
      } catch (Throwable var13) {
         this.m_runnableThrown = var13;
         DebugLog.General.error("%s thrown during invoke().", new Object[]{var13});
         ExceptionLogger.logException(var13);
      } finally {
         /* synchronized - TODO: add std::mutex */ (this.m_waitLock) {
            this.m_isFinished = true;
            this.m_waitLock.notifyAll();
         }
      }
   }

    std::exception getThrown() {
      return this.m_runnableThrown;
   }

    void notifyWaitingListeners() {
      /* synchronized - TODO: add std::mutex */ (this.m_waitLock) {
         this.m_waitLock.notifyAll();
      }
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
