#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FloorShaper {
public:
 protected int[] col = new int[4];
 int colTint = 0;
 bool isShore = false;
 protected float[] waterDepth = new float[4];

 void setVertColors(int int0, int int1, int int2, int int3) {
 this->col[0] = int0;
 this->col[1] = int1;
 this->col[2] = int2;
 this->col[3] = int3;
 }

 void setAlpha4(float float0) {
 int int0 = (int)(float0 * 255.0F) & 0xFF;
 this->col[0] = this->col[0] & 16777215 | int0 << 24;
 this->col[1] = this->col[1] & 16777215 | int0 << 24;
 this->col[2] = this->col[2] & 16777215 | int0 << 24;
 this->col[3] = this->col[3] & 16777215 | int0 << 24;
 }

 void setShore(bool boolean0) {
 this->isShore = boolean0;
 }

 void setWaterDepth(float float0, float float1, float float2, float float3) {
 this->waterDepth[0] = float0;
 this->waterDepth[1] = float1;
 this->waterDepth[2] = float2;
 this->waterDepth[3] = float3;
 }

 void setTintColor(int int0) {
 this->colTint = int0;
 }

 void accept(TextureDraw textureDraw) {
 if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.Lighting.getValue()) {
 textureDraw.col0 = Color.blendBGR(textureDraw.col0, this->col[0]);
 textureDraw.col1 = Color.blendBGR(textureDraw.col1, this->col[1]);
 textureDraw.col2 = Color.blendBGR(textureDraw.col2, this->col[2]);
 textureDraw.col3 = Color.blendBGR(textureDraw.col3, this->col[3]);
 }

 if (this->isShore && DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.ShoreFade.getValue()) {
 textureDraw.col0 = Color.setAlphaChannelToABGR(textureDraw.col0, 1.0F - this->waterDepth[0]);
 textureDraw.col1 = Color.setAlphaChannelToABGR(textureDraw.col1, 1.0F - this->waterDepth[1]);
 textureDraw.col2 = Color.setAlphaChannelToABGR(textureDraw.col2, 1.0F - this->waterDepth[2]);
 textureDraw.col3 = Color.setAlphaChannelToABGR(textureDraw.col3, 1.0F - this->waterDepth[3]);
 }

 if (this->colTint != 0) {
 textureDraw.col0 = Color.tintABGR(textureDraw.col0, this->colTint);
 textureDraw.col1 = Color.tintABGR(textureDraw.col1, this->colTint);
 textureDraw.col2 = Color.tintABGR(textureDraw.col2, this->colTint);
 textureDraw.col3 = Color.tintABGR(textureDraw.col3, this->colTint);
 }

 SpritePadding.applyIsoPadding(textureDraw, this->getIsoPaddingSettings());
 }

 private SpritePadding.IsoPaddingSettings getIsoPaddingSettings() {
 return SpritePaddingSettings.getSettings().IsoPadding;
 }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
