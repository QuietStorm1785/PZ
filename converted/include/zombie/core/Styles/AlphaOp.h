#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/ReadableColor.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace Styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * What to do with the alpha to the colours of a sprite
 */
enum class AlphaOp {
 PREMULTIPLY {
 int calc(ReadableColor readableColor, int int0) {
 float float0 = readableColor.getAlpha() * int0 * 0.003921569F;
 float float1 = float0 * 0.003921569F;
 return (int)(readableColor.getRed() * float1) << 0
 | (int)(readableColor.getGreen() * float1) << 8
 | (int)(readableColor.getBlue() * float1) << 16
 | (int)float0 << 24;
 }
 },
 KEEP {
 int calc(ReadableColor readableColor, int var2) {
 return readableColor.getRed() << 0 | readableColor.getGreen() << 8 | readableColor.getBlue() << 16 | readableColor.getAlpha() << 24;
 }
 },
 ZERO {
 int calc(ReadableColor readableColor, int int0) {
 float float0 = readableColor.getAlpha() * int0 * 0.003921569F;
 float float1 = float0 * 0.003921569F;
 return (int)(readableColor.getRed() * float1) << 0 | (int)(readableColor.getGreen() * float1) << 8 | (int)(readableColor.getBlue() * float1) << 16;
 }
 };

 static const float PREMULT_ALPHA = 0.003921569F;

 void op(ReadableColor c, int alpha, FloatBuffer dest) {
 dest.put(Float.intBitsToFloat(this->calc(c, alpha);
 }

 void op(int c, int alpha, FloatBuffer dest) {
 dest.put(Float.intBitsToFloat(c);
 }

 protected int calc(ReadableColor var1, int var2);
}
} // namespace Styles
} // namespace core
} // namespace zombie
