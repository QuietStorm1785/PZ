#pragma once
#include "org/lwjglx/opengl/Display.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/FPSGraph.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LightingThread {
public:
  static const LightingThread instance = new LightingThread();
  Thread lightingThread;
  bool bFinished = false;
public
  volatile boolean Interrupted = false;
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
        this.lightingThread = new Thread(
            ThreadGroups.Workers, ()->{
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
                } catch (Exception exception) {
                  exception.printStackTrace();
                }
              }
            });
        this.lightingThread.setPriority(5);
        this.lightingThread.setDaemon(true);
        this.lightingThread.setName("Lighting Thread");
        this.lightingThread.setUncaughtExceptionHandler(
            GameWindow::uncaughtException);
        this.lightingThread.start();
      }
    }
  }

  void GameLoadingUpdate() {}

  void update() {
    if (IsoWorld.instance != nullptr &&
        IsoWorld.instance.CurrentCell != nullptr) {
      if (LightingJNI.init) {
        LightingJNI.update();
      }
    }
  }

  void scrollLeft(int int0) {
    if (LightingJNI.init) {
      LightingJNI.scrollLeft(int0);
    }
  }

  void scrollRight(int int0) {
    if (LightingJNI.init) {
      LightingJNI.scrollRight(int0);
    }
  }

  void scrollUp(int int0) {
    if (LightingJNI.init) {
      LightingJNI.scrollUp(int0);
    }
  }

  void scrollDown(int int0) {
    if (LightingJNI.init) {
      LightingJNI.scrollDown(int0);
    }
  }
}
} // namespace iso
} // namespace zombie
