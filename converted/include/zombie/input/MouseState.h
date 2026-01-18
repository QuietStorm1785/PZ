#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class MouseState {
public:
 bool m_isCreated = false;
 private boolean[] m_buttonDownStates = nullptr;
 int m_mouseX = -1;
 int m_mouseY = -1;
 int m_wheelDelta = 0;
 bool m_wasPolled = false;

 void poll() {
 bool boolean0 = !this->m_isCreated;
 this->m_isCreated = this->m_isCreated || org.lwjglx.input.Mouse.isCreated();
 if (this->m_isCreated) {
 if (boolean0) {
 this->m_buttonDownStates = new boolean[org.lwjglx.input.Mouse.getButtonCount()];
 }

 this->m_mouseX = org.lwjglx.input.Mouse.getX();
 this->m_mouseY = org.lwjglx.input.Mouse.getY();
 this->m_wheelDelta = org.lwjglx.input.Mouse.getDWheel();
 this->m_wasPolled = true;

 for (int int0 = 0; int0 < this->m_buttonDownStates.length; int0++) {
 this->m_buttonDownStates[int0] = org.lwjglx.input.Mouse.isButtonDown(int0);
 }
 }
 }

 bool wasPolled() {
 return this->m_wasPolled;
 }

 void set(MouseState rhs) {
 this->m_isCreated = rhs.m_isCreated;
 if (rhs.m_buttonDownStates != nullptr) {
 if (this->m_buttonDownStates.empty() || this->m_buttonDownStates.length != rhs.m_buttonDownStates.length) {
 this->m_buttonDownStates = new boolean[rhs.m_buttonDownStates.length];
 }

 System.arraycopy(rhs.m_buttonDownStates, 0, this->m_buttonDownStates, 0, this->m_buttonDownStates.length);
 } else {
 this->m_buttonDownStates = nullptr;
 }

 this->m_mouseX = rhs.m_mouseX;
 this->m_mouseY = rhs.m_mouseY;
 this->m_wheelDelta = rhs.m_wheelDelta;
 this->m_wasPolled = rhs.m_wasPolled;
 }

 void reset() {
 this->m_wasPolled = false;
 }

 bool isCreated() {
 return this->m_isCreated;
 }

 int getX() {
 return this->m_mouseX;
 }

 int getY() {
 return this->m_mouseY;
 }

 int getDWheel() {
 return this->m_wheelDelta;
 }

 void resetDWheel() {
 this->m_wheelDelta = 0;
 }

 bool isButtonDown(int button) {
 return button >= this->m_buttonDownStates.length ? false : this->m_buttonDownStates[button];
 }

 int getButtonCount() {
 return this->isCreated() ? this->m_buttonDownStates.length : 0;
 }

 void setCursorPosition(int new_x, int new_y) {
 org.lwjglx.input.Mouse.setCursorPosition(new_x, new_y);
 }
}
} // namespace input
} // namespace zombie
