#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
// TODO: Replace with std::runtime_error or custom OpenGL exception
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugLogStream.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/ui/UITransition.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace logger {


class ExceptionLogger {
public:
    static int exceptionCount;
    static bool bIgnore;
    static bool bExceptionPopup = true;
    static long popupFrameMS = 0L;
    static UITransition transition = std::make_shared<UITransition>();
    static bool bHide;

   public static /* synchronized - TODO: add std::mutex */ void logException(Throwable var0) {
      logException(var0, nullptr);
   }

   public static /* synchronized - TODO: add std::mutex */ void logException(Throwable var0, std::string var1) {
      logException(var0, var1, DebugLog.General, LogSeverity.Error);
   }

   public static /* synchronized - TODO: add std::mutex */ void logException(Throwable var0, std::string var1, DebugLogStream var2, LogSeverity var3) {
    OpenGLException var4 = (OpenGLException)Type.tryCastTo(var0, OpenGLException.class);
      if (var4 != nullptr) {
         RenderThread.logGLException(var4, false);
      }

      var2.printException(var0, var1, DebugLogStream.generateCallerPrefix(), var3);

      try {
         if (bIgnore) {
            return;
         }

         bIgnore = true;
         exceptionCount++;
         if (!GameServer.bServer) {
            if (bExceptionPopup) {
               showPopup();
            }

            return;
         }
      } catch (Throwable var9) {
         var2.printException(var9, "Exception thrown while trying to logException.", LogSeverity.Error);
         return;
      } finally {
         bIgnore = false;
      }
   }

    static void showPopup() {
    float var0 = popupFrameMS > 0L ? transition.getElapsed() : 0.0F;
      popupFrameMS = 3000L;
      transition.setIgnoreUpdateTime(true);
      transition.init(500.0F, false);
      transition.setElapsed(var0);
      bHide = false;
   }

    static void render() {
      if (!UIManager.useUIFBO || Core.getInstance().UIRenderThisFrame) {
    bool var0 = false;
         if (var0) {
            popupFrameMS = 3000L;
         }

         if (popupFrameMS > 0L) {
            popupFrameMS = (long)(popupFrameMS - UIManager.getMillisSinceLastRender());
            transition.update();
    int var1 = TextManager.instance.getFontHeight(UIFont.DebugConsole);
    uint8_t var2 = 100;
    int var3 = var1 * 2 + 4;
    int var4 = Core.getInstance().getScreenWidth() - var2;
    int var5 = Core.getInstance().getScreenHeight() - (int)(var3 * transition.fraction());
            if (var0) {
               var5 = Core.getInstance().getScreenHeight() - var3;
            }

            SpriteRenderer.instance.renderi(nullptr, var4, var5, var2, var3, 0.8F, 0.0F, 0.0F, 1.0F, nullptr);
            SpriteRenderer.instance.renderi(nullptr, var4 + 1, var5 + 1, var2 - 2, var1 - 1, 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
            TextManager.instance.DrawStringCentre(UIFont.DebugConsole, var4 + var2 / 2, var5, "ERROR", 1.0, 0.0, 0.0, 1.0);
            TextManager.instance
               .DrawStringCentre(UIFont.DebugConsole, var4 + var2 / 2, var5 + var1, var0 ? "999" : int.toString(exceptionCount), 0.0, 0.0, 0.0, 1.0);
            if (popupFrameMS <= 0L && !bHide) {
               popupFrameMS = 500L;
               transition.init(500.0F, true);
               bHide = true;
            }
         }
      }
   }
}
} // namespace logger
} // namespace core
} // namespace zombie
