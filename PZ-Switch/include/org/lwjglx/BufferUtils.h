#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BufferUtils {
public:
 static ByteBuffer createByteBuffer(int int0) {
 return ByteBuffer.allocateDirect(int0).order(ByteOrder.nativeOrder());
 }

 static ShortBuffer createShortBuffer(int int0) {
 return createByteBuffer(int0 <<);
 }

 static CharBuffer createCharBuffer(int int0) {
 return createByteBuffer(int0 <<);
 }

 static IntBuffer createIntBuffer(int int0) {
 return createByteBuffer(int0 <<);
 }

 static LongBuffer createLongBuffer(int int0) {
 return createByteBuffer(int0 <<);
 }

 static FloatBuffer createFloatBuffer(int int0) {
 return createByteBuffer(int0 <<);
 }

 static DoubleBuffer createDoubleBuffer(int int0) {
 return createByteBuffer(int0 <<);
 }

 static int getElementSizeExponent(Buffer buffer) {
 if (dynamic_cast<ByteBuffer*>(buffer) != nullptr) {
 return 0;
 } else if (dynamic_cast<ShortBuffer*>(buffer) != nullptr || dynamic_cast<CharBuffer*>(buffer) != nullptr) {
 return 1;
 } else if (dynamic_cast<FloatBuffer*>(buffer) != nullptr || dynamic_cast<IntBuffer*>(buffer) != nullptr) {
 return 2;
 } else if (!(dynamic_cast<LongBuffer*>(buffer) != nullptr) &&
 !(dynamic_cast<DoubleBuffer*>(buffer) != nullptr) {
 throw IllegalStateException("Unsupported buffer type: " + buffer);
 } else {
 return 3;
 }
 }

 static int getOffset(Buffer buffer) {
 return buffer.position() << getElementSizeExponent(buffer);
 }

 static void zeroBuffer(ByteBuffer byteBuffer) {
 zeroBuffer0(byteBuffer, byteBuffer.position(), byteBuffer.remaining());
 }

 static void zeroBuffer(ShortBuffer shortBuffer) {
 zeroBuffer0(shortBuffer, shortBuffer.position() * 2L,
 shortBuffer.remaining() * 2L);
 }

 static void zeroBuffer(CharBuffer charBuffer) {
 zeroBuffer0(charBuffer, charBuffer.position() * 2L,
 charBuffer.remaining() * 2L);
 }

 static void zeroBuffer(IntBuffer intBuffer) {
 zeroBuffer0(intBuffer, intBuffer.position() * 4L,
 intBuffer.remaining() * 4L);
 }

 static void zeroBuffer(FloatBuffer floatBuffer) {
 zeroBuffer0(floatBuffer, floatBuffer.position() * 4L,
 floatBuffer.remaining() * 4L);
 }

 static void zeroBuffer(LongBuffer longBuffer) {
 zeroBuffer0(longBuffer, longBuffer.position() * 8L,
 longBuffer.remaining() * 8L);
 }

 static void zeroBuffer(DoubleBuffer doubleBuffer) {
 zeroBuffer0(doubleBuffer, doubleBuffer.position() * 8L,
 doubleBuffer.remaining() * 8L);
 }

private
 static void zeroBuffer0(Buffer var0, long var1, long var3);

 static long getBufferAddress(Buffer var0);
}
} // namespace lwjglx
} // namespace org
