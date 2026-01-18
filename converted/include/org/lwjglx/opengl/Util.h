#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL30.h"

namespace org {
namespace lwjglx {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Util {
public:
 private Util() {
 }

 static void checkGLError() {
 int int0 = GL30.glGetError();
 if (int0 != 0) {
 throw OpenGLException(int0);
 }
 }

 static std::string translateGLErrorString(int int0) {
 switch (int0) {
 case 0:
 return "No error";
 case 1280:
 return "Invalid enum";
 case 1281:
 return "Invalid value";
 case 1282:
 return "Invalid operation";
 case 1283:
 return "Stack overflow";
 case 1284:
 return "Stack underflow";
 case 1285:
 return "Out of memory";
 case 1286:
 return "Invalid framebuffer operation";
 case 32817:
 return "Table too large";
 default:
 return nullptr;
 }
 }
}
} // namespace opengl
} // namespace lwjglx
} // namespace org
