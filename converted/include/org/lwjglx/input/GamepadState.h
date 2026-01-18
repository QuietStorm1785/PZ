#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/glfw/GLFWGamepadState.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include <filesystem>

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GamepadState {
public:
 bool bPolled = false;
 const GLFWGamepadState axesButtons = GLFWGamepadState.malloc();
 const ByteBuffer hats = MemoryUtil.memAlloc(8);
 int hatState = 0;

 void set(GamepadState arg0) {
 this->bPolled = arg0.bPolled;
 this->axesButtons.set(arg0.axesButtons);
 this->hats.clear();
 arg0.hats.position(0);
 this->hats.put(arg0.hats);
 this->hatState = arg0.hatState;
 }

 void quit() {
 this->axesButtons.free();
 MemoryUtil.memFree(this->hats);
 }
}
} // namespace input
} // namespace lwjglx
} // namespace org
