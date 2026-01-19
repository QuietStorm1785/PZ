#pragma once
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/glfw/GLFWImage.h"
#include "org/lwjglx/BufferUtils.h"
#include "org/lwjglx/LWJGLException.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Cursor {
public:
 static const int CURSOR_ONE_BIT_TRANSPARENCY = 1;
 static const int CURSOR_8_BIT_ALPHA = 2;
 static const int CURSOR_ANIMATION = 4;
 long cursorHandle;

public
 Cursor(int arg0, int arg1, int arg2, int arg3, int arg4, IntBuffer arg5,
 IntBuffer arg6) {
 if (arg4 != 1) {
 System.out.println("ANIMATED CURSORS NOT YET SUPPORTED IN LWJGLX");
 } else {
 IntBuffer intBuffer = BufferUtils.createIntBuffer(arg5.limit());
 flipImages(arg0, arg1, arg4, arg5, intBuffer);
 ByteBuffer byteBuffer =
 convertARGBIntBuffertoRGBAByteBuffer(arg0, arg1, intBuffer);
 GLFWImage gLFWImage = GLFWImage.malloc();
 gLFWImage.width(arg0);
 gLFWImage.height(arg1);
 gLFWImage.pixels(byteBuffer);
 this->cursorHandle = GLFW.glfwCreateCursor(gLFWImage, arg2, arg3);
 if (this->cursorHandle == 0L) {
 throw RuntimeException("Error creating GLFW cursor");
 }
 }
 }

 static ByteBuffer convertARGBIntBuffertoRGBAByteBuffer(int int0, int int1,
 IntBuffer intBuffer) {
 ByteBuffer byteBuffer = BufferUtils.createByteBuffer(int0 * int1 * 4);

 for (int int2 = 0; int2 < intBuffer.limit(); int2++) {
 int int3 = intBuffer.get(int2);
 uint8_t byte0 = (byte)(int3 >>> 24);
 uint8_t byte1 = (byte)(int3 >>> 16);
 uint8_t byte2 = (byte)(int3 >>> 8);
 uint8_t byte3 = (byte)int3;
 byteBuffer.put(byte3);
 byteBuffer.put(byte2);
 byteBuffer.put(byte1);
 byteBuffer.put(byte0);
 }

 byteBuffer.flip();
 return byteBuffer;
 }

 static int getMinCursorSize() noexcept{ return 1; }

 static int getMaxCursorSize() noexcept{ return 512; }

 static int getCapabilities() { return 2; }

 static void flipImages(int int4, int int3, int int1, IntBuffer intBuffer0,
 IntBuffer intBuffer1) {
 for (int int0 = 0; int0 < int1; int0++) {
 int int2 = int0 * int4 * int3;
 flipImage(int4, int3, int2, intBuffer0, intBuffer1);
 }
 }

 static void flipImage(int int4, int int1, int int3, IntBuffer intBuffer0,
 IntBuffer intBuffer1) {
 for (int int0 = 0; int0 < int1 >> 1; int0++) {
 int int2 = int0 * int4 + int3;
 int int5 = (int1 - int0 - 1) * int4 + int3;

 for (int int6 = 0; int6 < int4; int6++) {
 int int7 = int2 + int6;
 int int8 = int5 + int6;
 int int9 = intBuffer0.get(int7 + intBuffer0.position());
 intBuffer1.put(int7, intBuffer0.get(int8 + intBuffer0.position()));
 intBuffer1.put(int8, int9);
 }
 }
 }

 long getHandle() { return this->cursorHandle; }

 void destroy() { GLFW.glfwDestroyCursor(this->cursorHandle); }
}
} // namespace input
} // namespace lwjglx
} // namespace org
