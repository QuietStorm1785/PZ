#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
// TODO: Replace with SDL2 input or custom input handling
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/input/ControllerState.h"
#include "zombie/input/ControllerStateCache.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"

namespace zombie {
namespace core {
namespace input {


class Input {
public:
    static const int ANY_CONTROLLER = -1;
   private const Controller[] controllers = new Controller[16];
   private const std::vector<Controller> newlyConnected = std::make_unique<std::vector<>>();
   private const std::vector<Controller> newlyDisconnected = std::make_unique<std::vector<>>();
   private const boolean[][] controllerPressed = new boolean[16][15];
   private const boolean[][] controllerWasPressed = new boolean[16][15];
   private const float[][] controllerPov = new float[16][2];
    const ControllerStateCache m_controllerStateCache = std::make_shared<ControllerStateCache>();

    static std::string getKeyName(int var0) {
    std::string var1 = Keyboard.getKeyName(var0);
      if ("LSHIFT" == var1)) {
         var1 = "Left SHIFT";
      }

      if ("RSHIFT" == var1)) {
         var1 = "Right SHIFT";
      }

      if ("LMENU" == var1)) {
         var1 = "Left ALT";
      } else if ("RMENU" == var1)) {
         var1 = "Right ALT";
      }

    return var1;
   }

    static int getKeyCode(const std::string& var0) {
      if ("Right SHIFT" == var0)) {
    return 54;
      } else if ("Left SHIFT" == var0)) {
    return 42;
      } else if ("Left ALT" == var0)) {
    return 56;
      } else {
         return "Right ALT" == var0) ? 184 : Keyboard.getKeyIndex(var0);
      }
   }

    int getControllerCount() {
      return this.controllers.length;
   }

    int getAxisCount(int var1) {
    Controller var2 = this.getController(var1);
    return var2 = = nullptr ? 0 : var2.getAxisCount();
   }

    float getAxisValue(int var1, int var2) {
    Controller var3 = this.getController(var1);
    return var3 = = nullptr ? 0.0F : var3.getAxisValue(var2);
   }

    std::string getAxisName(int var1, int var2) {
    Controller var3 = this.getController(var1);
    return var3 = = nullptr ? nullptr : var3.getAxisName(var2);
   }

    bool isControllerLeftD(int var1) {
      if (var1 == -1) {
         for (int var3 = 0; var3 < this.controllers.length; var3++) {
            if (this.isControllerLeftD(var3)) {
    return true;
            }
         }

    return false;
      } else {
    Controller var2 = this.getController(var1);
    return var2 = = nullptr ? false : var2.getPovX() < -0.5F;
      }
   }

    bool isControllerRightD(int var1) {
      if (var1 == -1) {
         for (int var3 = 0; var3 < this.controllers.length; var3++) {
            if (this.isControllerRightD(var3)) {
    return true;
            }
         }

    return false;
      } else {
    Controller var2 = this.getController(var1);
    return var2 = = nullptr ? false : var2.getPovX() > 0.5F;
      }
   }

    bool isControllerUpD(int var1) {
      if (var1 == -1) {
         for (int var3 = 0; var3 < this.controllers.length; var3++) {
            if (this.isControllerUpD(var3)) {
    return true;
            }
         }

    return false;
      } else {
    Controller var2 = this.getController(var1);
    return var2 = = nullptr ? false : var2.getPovY() < -0.5F;
      }
   }

    bool isControllerDownD(int var1) {
      if (var1 == -1) {
         for (int var3 = 0; var3 < this.controllers.length; var3++) {
            if (this.isControllerDownD(var3)) {
    return true;
            }
         }

    return false;
      } else {
    Controller var2 = this.getController(var1);
    return var2 = = nullptr ? false : var2.getPovY() > 0.5F;
      }
   }

    Controller checkControllerButton(int var1, int var2) {
    Controller var3 = this.getController(var1);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         return var2 >= 0 && var2 < var3.getButtonCount() ? var3 : nullptr;
      }
   }

    bool isButtonPressedD(int var1, int var2) {
      if (var2 == -1) {
         for (int var4 = 0; var4 < this.controllers.length; var4++) {
            if (this.isButtonPressedD(var1, var4)) {
    return true;
            }
         }

    return false;
      } else {
    Controller var3 = this.checkControllerButton(var2, var1);
    return var3 = = nullptr ? false : this.controllerPressed[var2][var1];
      }
   }

    bool wasButtonPressed(int var1, int var2) {
    Controller var3 = this.checkControllerButton(var1, var2);
    return var3 = = nullptr ? false : this.controllerWasPressed[var1][var2];
   }

    bool isButtonStartPress(int var1, int var2) {
      return !this.wasButtonPressed(var1, var2) && this.isButtonPressedD(var2, var1);
   }

    bool isButtonReleasePress(int var1, int var2) {
      return this.wasButtonPressed(var1, var2) && !this.isButtonPressedD(var2, var1);
   }

    void initControllers() {
      this.updateGameThread();
      this.updateGameThread();
   }

    void onControllerConnected(Controller var1) {
      JoypadManager.instance.onControllerConnected(var1);
      if (LuaManager.env != nullptr) {
         LuaEventManager.triggerEvent("OnGamepadConnect", var1.getID());
      }
   }

    void onControllerDisconnected(Controller var1) {
      JoypadManager.instance.onControllerDisconnected(var1);
      if (LuaManager.env != nullptr) {
         LuaEventManager.triggerEvent("OnGamepadDisconnect", var1.getID());
      }
   }

    void poll() {
      if (!Core.getInstance().isDoingTextEntry()) {
         while (GameKeyboard.getEventQueuePolling().next()) {
         }
      }

      while (Mouse.next()) {
      }

      this.m_controllerStateCache.poll();
   }

    Controller getController(int var1) {
      return var1 >= 0 && var1 < this.controllers.length ? this.controllers[var1] : nullptr;
   }

    int getButtonCount(int var1) {
    Controller var2 = this.getController(var1);
    return var2 = = nullptr ? nullptr : var2.getButtonCount();
   }

    std::string getButtonName(int var1, int var2) {
    Controller var3 = this.getController(var1);
    return var3 = = nullptr ? nullptr : var3.getButtonName(var2);
   }

    void updateGameThread() {
      if (!this.m_controllerStateCache.getState().isCreated()) {
         this.m_controllerStateCache.swap();
      } else {
    ControllerState var1 = this.m_controllerStateCache.getState();
         if (this.checkConnectDisconnect(var1)) {
            for (int var2 = 0; var2 < this.newlyDisconnected.size(); var2++) {
    Controller var3 = this.newlyDisconnected.get(var2);
               this.onControllerDisconnected(var3);
            }

            for (int var7 = 0; var7 < this.newlyConnected.size(); var7++) {
    Controller var9 = this.newlyConnected.get(var7);
               this.onControllerConnected(var9);
            }
         }

         for (int var8 = 0; var8 < this.getControllerCount(); var8++) {
    Controller var10 = this.getController(var8);
            if (var10 != nullptr) {
    int var4 = var10.getButtonCount();

               for (int var5 = 0; var5 < var4; var5++) {
                  this.controllerWasPressed[var8][var5] = this.controllerPressed[var8][var5];
                  if (this.controllerPressed[var8][var5] && !var10.isButtonPressed(var5)) {
                     this.controllerPressed[var8][var5] = false;
                  } else if (!this.controllerPressed[var8][var5] && var10.isButtonPressed(var5)) {
                     this.controllerPressed[var8][var5] = true;
                     JoypadManager.instance.onPressed(var8, var5);
                  }
               }

               var4 = var10.getAxisCount();

               for (int var12 = 0; var12 < var4; var12++) {
    float var6 = var10.getAxisValue(var12);
                  if ((!var10.isGamepad() || var12 != 4) && var12 != 5) {
                     if (var6 < -0.5F) {
                        JoypadManager.instance.onPressedAxisNeg(var8, var12);
                     }

                     if (var6 > 0.5F) {
                        JoypadManager.instance.onPressedAxis(var8, var12);
                     }
                  } else if (var6 > 0.0F) {
                     JoypadManager.instance.onPressedTrigger(var8, var12);
                  }
               }

    float var13 = var10.getPovX();
    float var14 = var10.getPovY();
               if (var13 != this.controllerPov[var8][0] || var14 != this.controllerPov[var8][1]) {
                  this.controllerPov[var8][0] = var13;
                  this.controllerPov[var8][1] = var14;
                  JoypadManager.instance.onPressedPov(var8);
               }
            }
         }

         this.m_controllerStateCache.swap();
      }
   }

    bool checkConnectDisconnect(ControllerState var1) {
    bool var2 = false;
      this.newlyConnected.clear();
      this.newlyDisconnected.clear();

      for (int var3 = 0; var3 < 16; var3++) {
    Controller var4 = var1.getController(var3);
         if (var4 != this.controllers[var3]) {
            var2 = true;
            if (var4 != nullptr && var4.isGamepad()) {
               this.newlyConnected.push_back(var4);
            } else {
               if (this.controllers[var3] != nullptr) {
                  this.newlyDisconnected.push_back(this.controllers[var3]);
               }

               var4 = nullptr;
            }

            this.controllers[var3] = var4;
         }
      }

    return var2;
   }

    void quit() {
      this.m_controllerStateCache.quit();
   }
}
} // namespace input
} // namespace core
} // namespace zombie
