#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/Mouse.h"

namespace zombie {
namespace input {


class MouseState {
public:
    bool m_isCreated = false;
   private boolean[] m_buttonDownStates = nullptr;
    int m_mouseX = -1;
    int m_mouseY = -1;
    int m_wheelDelta = 0;
    bool m_wasPolled = false;

    void poll() {
    bool var1 = !this.m_isCreated;
      this.m_isCreated = this.m_isCreated || Mouse.isCreated();
      if (this.m_isCreated) {
         if (var1) {
            this.m_buttonDownStates = new boolean[Mouse.getButtonCount()];
         }

         this.m_mouseX = Mouse.getX();
         this.m_mouseY = Mouse.getY();
         this.m_wheelDelta = Mouse.getDWheel();
         this.m_wasPolled = true;

         for (int var2 = 0; var2 < this.m_buttonDownStates.length; var2++) {
            this.m_buttonDownStates[var2] = Mouse.isButtonDown(var2);
         }
      }
   }

    bool wasPolled() {
      return this.m_wasPolled;
   }

    void set(MouseState var1) {
      this.m_isCreated = var1.m_isCreated;
      if (var1.m_buttonDownStates != nullptr) {
         if (this.m_buttonDownStates == nullptr || this.m_buttonDownStates.length != var1.m_buttonDownStates.length) {
            this.m_buttonDownStates = new boolean[var1.m_buttonDownStates.length];
         }

         System.arraycopy(var1.m_buttonDownStates, 0, this.m_buttonDownStates, 0, this.m_buttonDownStates.length);
      } else {
         this.m_buttonDownStates = nullptr;
      }

      this.m_mouseX = var1.m_mouseX;
      this.m_mouseY = var1.m_mouseY;
      this.m_wheelDelta = var1.m_wheelDelta;
      this.m_wasPolled = var1.m_wasPolled;
   }

    void reset() {
      this.m_wasPolled = false;
   }

    bool isCreated() {
      return this.m_isCreated;
   }

    int getX() {
      return this.m_mouseX;
   }

    int getY() {
      return this.m_mouseY;
   }

    int getDWheel() {
      return this.m_wheelDelta;
   }

    void resetDWheel() {
      this.m_wheelDelta = 0;
   }

    bool isButtonDown(int var1) {
      return var1 >= this.m_buttonDownStates.length ? false : this.m_buttonDownStates[var1];
   }

    int getButtonCount() {
      return this.isCreated() ? this.m_buttonDownStates.length : 0;
   }

    void setCursorPosition(int var1, int var2) {
      Mouse.setCursorPosition(var1, var2);
   }
}
} // namespace input
} // namespace zombie
