#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/opengl/Display.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/FPSGraph.h"

namespace zombie {
namespace iso {


class LightingThread {
public:
    static const LightingThread instance = std::make_shared<LightingThread>();
    Thread lightingThread;
    bool bFinished = false;
   public volatile boolean Interrupted = false;
    static bool DebugLockTime = false;

    void stop() {
      if (!PerformanceSettings.LightingThread) {
         LightingJNI.stop();
      } else {
         this.bFinished = true;

         while (this.lightingThread.isAlive()) {
         }

         LightingJNI.stop();
         this.lightingThread = nullptr;
      }
   }

    void create() {
      if (!GameServer.bServer) {
         if (PerformanceSettings.LightingThread) {
            this.bFinished = false;
            this.lightingThread = std::make_shared<Thread>(ThreadGroups.Workers, () -> {
               while (!this.bFinished) {
                  if (IsoWorld.instance.CurrentCell == nullptr) {
                     return;
                  }

                  try {
                     Display.sync(PerformanceSettings.LightingFPS);
                     LightingJNI.DoLightingUpdateNew(System.nanoTime());

                     while (LightingJNI.WaitingForMain() && !this.bFinished) {
                        Thread.sleep(13L);
                     }

                     if (Core.bDebug && FPSGraph.instance != nullptr) {
                        FPSGraph.instance.addLighting(System.currentTimeMillis());
                     }
                  } catch (Exception var2) {
                     var2.printStackTrace();
                  }
               }
            });
            this.lightingThread.setPriority(5);
            this.lightingThread.setDaemon(true);
            this.lightingThread.setName("Lighting Thread");
            this.lightingThread.setUncaughtExceptionHandler(GameWindow::uncaughtException);
            this.lightingThread.start();
         }
      }
   }

    void GameLoadingUpdate() {
   }

    void update() {
      if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr) {
         if (LightingJNI.init) {
            LightingJNI.update();
         }
      }
   }

    void scrollLeft(int var1) {
      if (LightingJNI.init) {
         LightingJNI.scrollLeft(var1);
      }
   }

    void scrollRight(int var1) {
      if (LightingJNI.init) {
         LightingJNI.scrollRight(var1);
      }
   }

    void scrollUp(int var1) {
      if (LightingJNI.init) {
         LightingJNI.scrollUp(var1);
      }
   }

    void scrollDown(int var1) {
      if (LightingJNI.init) {
         LightingJNI.scrollDown(var1);
      }
   }
}
} // namespace iso
} // namespace zombie
