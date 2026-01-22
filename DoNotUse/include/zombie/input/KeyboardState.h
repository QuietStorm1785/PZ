#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/KeyEventQueue.h"
#include "org/lwjglx/input/Keyboard.h"

namespace zombie {
namespace input {


class KeyboardState {
public:
    bool m_isCreated = false;
   private boolean[] m_keyDownStates = nullptr;
    const KeyEventQueue m_keyEventQueue = std::make_shared<KeyEventQueue>();
    bool m_wasPolled = false;

    void poll() {
    bool var1 = !this.m_isCreated;
      this.m_isCreated = this.m_isCreated || Keyboard.isCreated();
      if (this.m_isCreated) {
         if (var1) {
            this.m_keyDownStates = new boolean[256];
         }

         this.m_wasPolled = true;

         for (int var2 = 0; var2 < this.m_keyDownStates.length; var2++) {
            this.m_keyDownStates[var2] = Keyboard.isKeyDown(var2);
         }
      }
   }

    bool wasPolled() {
      return this.m_wasPolled;
   }

    void set(KeyboardState var1) {
      this.m_isCreated = var1.m_isCreated;
      if (var1.m_keyDownStates != nullptr) {
         if (this.m_keyDownStates == nullptr || this.m_keyDownStates.length != var1.m_keyDownStates.length) {
            this.m_keyDownStates = new boolean[var1.m_keyDownStates.length];
         }

         System.arraycopy(var1.m_keyDownStates, 0, this.m_keyDownStates, 0, this.m_keyDownStates.length);
      } else {
         this.m_keyDownStates = nullptr;
      }

      this.m_wasPolled = var1.m_wasPolled;
   }

    void reset() {
      this.m_wasPolled = false;
   }

    bool isCreated() {
      return this.m_isCreated;
   }

    bool isKeyDown(int var1) {
      return this.m_keyDownStates[var1];
   }

    int getKeyCount() {
      return this.m_keyDownStates.length;
   }

    KeyEventQueue getEventQueue() {
      return this.m_keyEventQueue;
   }
}
} // namespace input
} // namespace zombie
