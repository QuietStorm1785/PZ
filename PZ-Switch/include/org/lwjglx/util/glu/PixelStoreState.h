#pragma once
#include "org/lwjgl/opengl/GL11.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PixelStoreState : public Util {
public:
 int unpackRowLength;
 int unpackAlignment;
 int unpackSkipRows;
 int unpackSkipPixels;
 int packRowLength;
 int packAlignment;
 int packSkipRows;
 int packSkipPixels;

 PixelStoreState() { this->load(); }

 void load() {
 this->unpackRowLength = GL11.glGetInteger(3314);
 this->unpackAlignment = GL11.glGetInteger(3317);
 this->unpackSkipRows = GL11.glGetInteger(3315);
 this->unpackSkipPixels = GL11.glGetInteger(3316);
 this->packRowLength = GL11.glGetInteger(3330);
 this->packAlignment = GL11.glGetInteger(3333);
 this->packSkipRows = GL11.glGetInteger(3331);
 this->packSkipPixels = GL11.glGetInteger(3332);
 }

 void save() {
 GL11.glPixelStorei(3314, this->unpackRowLength);
 GL11.glPixelStorei(3317, this->unpackAlignment);
 GL11.glPixelStorei(3315, this->unpackSkipRows);
 GL11.glPixelStorei(3316, this->unpackSkipPixels);
 GL11.glPixelStorei(3330, this->packRowLength);
 GL11.glPixelStorei(3333, this->packAlignment);
 GL11.glPixelStorei(3331, this->packSkipRows);
 GL11.glPixelStorei(3332, this->packSkipPixels);
 }
}
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
