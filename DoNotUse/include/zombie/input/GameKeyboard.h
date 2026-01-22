#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/KeyEventQueue.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace input {


class GameKeyboard {
public:
   private static boolean[] bDown;
   private static boolean[] bLastDown;
   private static boolean[] bEatKey;
    static bool bNoEventsWhileLoading = false;
    static bool doLuaKeyPressed = true;
    static const KeyboardStateCache s_keyboardStateCache = std::make_shared<KeyboardStateCache>();

    static void update() {
      if (!s_keyboardStateCache.getState().isCreated()) {
         s_keyboardStateCache.swap();
      } else {
    int var0 = s_keyboardStateCache.getState().getKeyCount();
         if (bDown == nullptr) {
            bDown = new boolean[var0];
            bLastDown = new boolean[var0];
            bEatKey = new boolean[var0];
         }

    bool var1 = Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry;

         for (int var2 = 1; var2 < var0; var2++) {
            bLastDown[var2] = bDown[var2];
            bDown[var2] = s_keyboardStateCache.getState().isKeyDown(var2);
            if (!bDown[var2] && bLastDown[var2]) {
               if (bEatKey[var2]) {
                  bEatKey[var2] = false;
                  continue;
               }

               if (bNoEventsWhileLoading || var1 || LuaManager.thread == UIManager.defaultthread && UIManager.onKeyRelease(var2)) {
                  continue;
               }

               if (Core.bDebug && !doLuaKeyPressed) {
                  System.out.println("KEY RELEASED " + var2 + " doLuaKeyPressed=false");
               }

               if (LuaManager.thread == UIManager.defaultthread && doLuaKeyPressed) {
                  LuaEventManager.triggerEvent("OnKeyPressed", var2);
               }

               if (LuaManager.thread == UIManager.defaultthread) {
                  LuaEventManager.triggerEvent("OnCustomUIKey", var2);
                  LuaEventManager.triggerEvent("OnCustomUIKeyReleased", var2);
               }
            }

            if (bDown[var2] && bLastDown[var2]) {
               if (bNoEventsWhileLoading || var1 || LuaManager.thread == UIManager.defaultthread && UIManager.onKeyRepeat(var2)) {
                  continue;
               }

               if (LuaManager.thread == UIManager.defaultthread && doLuaKeyPressed) {
                  LuaEventManager.triggerEvent("OnKeyKeepPressed", var2);
               }
            }

            if (bDown[var2]
               && !bLastDown[var2]
               && !bNoEventsWhileLoading
               && !var1
               && !bEatKey[var2]
               && (LuaManager.thread != UIManager.defaultthread || !UIManager.onKeyPress(var2))
               && !bEatKey[var2]) {
               if (LuaManager.thread == UIManager.defaultthread && doLuaKeyPressed) {
                  LuaEventManager.triggerEvent("OnKeyStartPressed", var2);
               }

               if (LuaManager.thread == UIManager.defaultthread) {
                  LuaEventManager.triggerEvent("OnCustomUIKeyPressed", var2);
               }
            }
         }

         s_keyboardStateCache.swap();
      }
   }

    static void poll() {
      s_keyboardStateCache.poll();
   }

    static bool isKeyPressed(int var0) {
    return isKeyDown();
   }

    static bool isKeyDown(int var0) {
      if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry) {
    return false;
      } else {
    return bDown = = nullptr ? false : bDown[var0];
      }
   }

    static bool wasKeyDown(int var0) {
      if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry) {
    return false;
      } else {
    return bLastDown = = nullptr ? false : bLastDown[var0];
      }
   }

    static void eatKeyPress(int var0) {
      if (var0 >= 0 && var0 < bEatKey.length) {
         bEatKey[var0] = true;
      }
   }

    static void setDoLuaKeyPressed(bool var0) {
      doLuaKeyPressed = var0;
   }

    static KeyEventQueue getEventQueue() {
      assert Thread.currentThread() == GameWindow.GameThread;

      return s_keyboardStateCache.getState().getEventQueue();
   }

    static KeyEventQueue getEventQueuePolling() {
      assert Thread.currentThread() == RenderThread.RenderThread;

      return s_keyboardStateCache.getStatePolling().getEventQueue();
   }
}
} // namespace input
} // namespace zombie
