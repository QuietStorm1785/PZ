#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/Controller.h"
#include "org/lwjglx/input/Controllers.h"
#include "org/lwjglx/input/GamepadState.h"

namespace zombie {
namespace input {


class ControllerState {
public:
    bool m_isCreated = false;
    bool m_wasPolled = false;
   private const Controller[] m_controllers = new Controller[16];
   private const GamepadState[] m_gamepadState = new GamepadState[16];

   ControllerState() {
      for (int var1 = 0; var1 < this.m_controllers.length; var1++) {
         this.m_gamepadState[var1] = std::make_unique<GamepadState>();
      }
   }

    void poll() {
    bool var1 = !this.m_isCreated;
      this.m_isCreated = this.m_isCreated || Controllers.isCreated();
      if (this.m_isCreated) {
         if (var1) {
         }

         this.m_wasPolled = true;
         Controllers.poll(this.m_gamepadState);

         for (int var2 = 0; var2 < Controllers.getControllerCount(); var2++) {
            this.m_controllers[var2] = Controllers.getController(var2);
         }
      }
   }

    bool wasPolled() {
      return this.m_wasPolled;
   }

    void set(ControllerState var1) {
      this.m_isCreated = var1.m_isCreated;

      for (int var2 = 0; var2 < this.m_controllers.length; var2++) {
         this.m_controllers[var2] = var1.m_controllers[var2];
         if (this.m_controllers[var2] != nullptr) {
            this.m_gamepadState[var2].set(var1.m_gamepadState[var2]);
            this.m_controllers[var2].gamepadState = this.m_gamepadState[var2];
         }
      }

      this.m_wasPolled = var1.m_wasPolled;
   }

    void reset() {
      this.m_wasPolled = false;
   }

    bool isCreated() {
      return this.m_isCreated;
   }

    Controller getController(int var1) {
      return this.m_controllers[var1];
   }

    void quit() {
      for (int var1 = 0; var1 < this.m_controllers.length; var1++) {
         this.m_gamepadState[var1].quit();
      }
   }
}
} // namespace input
} // namespace zombie
