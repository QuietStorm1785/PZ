#pragma once
#include "org/lwjglx/input/KeyEventQueue.h"
#include "org/lwjglx/input/Keyboard.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KeyboardState {
public:
 bool m_isCreated = false;
private
 boolean[] m_keyDownStates = nullptr;
 const KeyEventQueue m_keyEventQueue = new KeyEventQueue();
 bool m_wasPolled = false;

 void poll() {
 bool boolean0 = !this->m_isCreated;
 this->m_isCreated = this->m_isCreated || Keyboard.isCreated();
 if (this->m_isCreated) {
 if (boolean0) {
 this->m_keyDownStates = new boolean[256];
 }

 this->m_wasPolled = true;

 for (int int0 = 0; int0 < this->m_keyDownStates.length; int0++) {
 this->m_keyDownStates[int0] = Keyboard.isKeyDown(int0);
 }
 }
 }

 bool wasPolled() { return this->m_wasPolled; }

 void set(KeyboardState rhs) {
 this->m_isCreated = rhs.m_isCreated;
 if (rhs.m_keyDownStates != nullptr) {
 if (this->m_keyDownStates.empty() ||
 this->m_keyDownStates.length != rhs.m_keyDownStates.length) {
 this->m_keyDownStates = new boolean[rhs.m_keyDownStates.length];
 }

 System.arraycopy(rhs.m_keyDownStates, 0, this->m_keyDownStates, 0,
 this->m_keyDownStates.length);
 } else {
 this->m_keyDownStates = nullptr;
 }

 this->m_wasPolled = rhs.m_wasPolled;
 }

 void reset() { this->m_wasPolled = false; }

 bool isCreated() { return this->m_isCreated; }

 bool isKeyDown(int button) { return this->m_keyDownStates[button]; }

 int getKeyCount() noexcept{ return this->m_keyDownStates.length; }

 KeyEventQueue getEventQueue() { return this->m_keyEventQueue; }
}
} // namespace input
} // namespace zombie
