#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/glfw/GLFW.h"

namespace org {
namespace lwjglx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Sys {
public:
 static long getTimerResolution() {
 return 1000L;
 }

 static long getTime() {
 return (long)(GLFW.glfwGetTime() * 1000.0);
 }

 static long getNanoTime() {
 return (long)(GLFW.glfwGetTime() * 1.0E9);
 }
}
} // namespace lwjglx
} // namespace org
