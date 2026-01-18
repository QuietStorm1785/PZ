#pragma once
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureBinder {
public:
 static TextureBinder instance = new TextureBinder();
 int maxTextureUnits = 0;
public
 int[] textureUnitIDs;
 int textureUnitIDStart = 33984;
 int textureIndex = 0;
 int activeTextureIndex = 0;

public
 TextureBinder() {
 this->maxTextureUnits = 1;
 this->textureUnitIDs = new int[this->maxTextureUnits];

 for (int int0 = 0; int0 < this->maxTextureUnits; int0++) {
 this->textureUnitIDs[int0] = -1;
 }
 }

 void bind(int int1) {
 for (int int0 = 0; int0 < this->maxTextureUnits; int0++) {
 if (this->textureUnitIDs[int0] == int1) {
 int int2 = int0 + this->textureUnitIDStart;
 GL13.glActiveTexture(int2);
 this->activeTextureIndex = int2;
 return;
 }
 }

 this->textureUnitIDs[this->textureIndex] = int1;
 GL13.glActiveTexture(this->textureUnitIDStart + this->textureIndex);
 GL11.glBindTexture(3553, int1);
 this->activeTextureIndex = this->textureUnitIDStart + this->textureIndex;
 this->textureIndex++;
 if (this->textureIndex >= this->maxTextureUnits) {
 this->textureIndex = 0;
 }
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
