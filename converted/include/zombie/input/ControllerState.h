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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ControllerState {
public:
 bool m_isCreated = false;
 bool m_wasPolled = false;
 private Controller[] m_controllers = new Controller[16];
 private GamepadState[] m_gamepadState = new GamepadState[16];

 ControllerState() {
 for (int int0 = 0; int0 < this->m_controllers.length; int0++) {
 this->m_gamepadState[int0] = std::make_unique<GamepadState>();
 }
 }

 void poll() {
 bool boolean0 = !this->m_isCreated;
 this->m_isCreated = this->m_isCreated || Controllers.isCreated();
 if (this->m_isCreated) {
 if (boolean0) {
 }

 this->m_wasPolled = true;
 Controllers.poll(this->m_gamepadState);

 for (int int0 = 0; int0 < Controllers.getControllerCount(); int0++) {
 this->m_controllers[int0] = Controllers.getController(int0);
 }
 }
 }

 bool wasPolled() {
 return this->m_wasPolled;
 }

 void set(ControllerState rhs) {
 this->m_isCreated = rhs.m_isCreated;

 for (int int0 = 0; int0 < this->m_controllers.length; int0++) {
 this->m_controllers[int0] = rhs.m_controllers[int0];
 if (this->m_controllers[int0] != nullptr) {
 this->m_gamepadState[int0].set(rhs.m_gamepadState[int0]);
 this->m_controllers[int0].gamepadState = this->m_gamepadState[int0];
 }
 }

 this->m_wasPolled = rhs.m_wasPolled;
 }

 void reset() {
 this->m_wasPolled = false;
 }

 bool isCreated() {
 return this->m_isCreated;
 }

 Controller getController(int index) {
 return this->m_controllers[index];
 }

 void quit() {
 for (int int0 = 0; int0 < this->m_controllers.length; int0++) {
 this->m_gamepadState[int0].quit();
 }
 }
}
} // namespace input
} // namespace zombie
