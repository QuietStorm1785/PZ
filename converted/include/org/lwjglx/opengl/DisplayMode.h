#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace lwjglx {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class DisplayMode {
public:
 const int width;
 const int height;
 const int bpp;
 const int freq;
 const bool fullscreen;

 public DisplayMode(int int0, int int1) {
 this(int0, int1, 0, 0, false);
 }

 DisplayMode(int int0, int int1, int int2, int int3) {
 this(int0, int1, int2, int3, true);
 }

 private DisplayMode(int int0, int int1, int int2, int int3, bool boolean0) {
 this->width = int0;
 this->height = int1;
 this->bpp = int2;
 this->freq = int3;
 this->fullscreen = boolean0;
 }

 bool isFullscreenCapable() {
 return this->fullscreen;
 }

 int getWidth() {
 return this->width;
 }

 int getHeight() {
 return this->height;
 }

 int getBitsPerPixel() {
 return this->bpp;
 }

 int getFrequency() {
 return this->freq;
 }

 bool equals(void* object) {
 return object != nullptr && object instanceof DisplayMode displayMode1
 ? displayMode1.width == this->width && displayMode1.height == this->height && displayMode1.bpp == this->bpp && displayMode1.freq == this->freq
 : false;
 }

 int hashCode() {
 return this->width ^ this->height ^ this->freq ^ this->bpp;
 }

 std::string toString() {
 StringBuilder stringBuilder = new StringBuilder(32);
 stringBuilder.append(this->width);
 stringBuilder.append(" x ");
 stringBuilder.append(this->height);
 stringBuilder.append(" x ");
 stringBuilder.append(this->bpp);
 stringBuilder.append(" @");
 stringBuilder.append(this->freq);
 stringBuilder.append("Hz");
 return stringBuilder.toString();
 }
}
} // namespace opengl
} // namespace lwjglx
} // namespace org
