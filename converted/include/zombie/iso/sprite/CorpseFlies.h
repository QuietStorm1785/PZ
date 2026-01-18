#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CorpseFlies {
public:
 static Texture TEXTURE;
 static const int FRAME_WIDTH = 128;
 static const int FRAME_HEIGHT = 128;
 static const int COLUMNS = 8;
 static const int ROWS = 7;
 static const int NUM_FRAMES = 56;
 static float COUNTER = 0.0F;
 static int FRAME = 0;

 static void render(int int1, int int2, int int5) {
 if (TEXTURE == nullptr) {
 TEXTURE = Texture.getSharedTexture("media/textures/CorpseFlies.png");
 }

 if (TEXTURE != nullptr && TEXTURE.isReady()) {
 int int0 = (FRAME + int1 + int2) % 56;
 int int3 = int0 % 8;
 int int4 = int0 / 8;
 float float0 = (float)(int3 * 128) / TEXTURE.getWidth();
 float float1 = (float)(int4 * 128) / TEXTURE.getHeight();
 float float2 = (float)((int3 + 1) * 128) / TEXTURE.getWidth();
 float float3 = (float)((int4 + 1) * 128) / TEXTURE.getHeight();
 float float4 = IsoUtils.XToScreen(int1 + 0.5F, int2 + 0.5F, int5, 0) + IsoSprite.globalOffsetX;
 float float5 = IsoUtils.YToScreen(int1 + 0.5F, int2 + 0.5F, int5, 0) + IsoSprite.globalOffsetY;
 uint8_t byte0 = 64;
 int int6 = byte0 * Core.TileScale;
 float4 -= int6 / 2;
 float5 -= int6 + 16 * Core.TileScale;
 if (Core.bDebug) {
 }

 SpriteRenderer.instance
 .render(TEXTURE, float4, float5, int6, int6, 1.0F, 1.0F, 1.0F, 1.0F, float0, float1, float2, float1, float2, float3, float0, float3);
 }
 }

 static void update() {
 if (!GameServer.bServer) {
 COUNTER = COUNTER + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * 1000.0F;
 float float0 = 20.0F;
 if (COUNTER > 1000.0F / float0) {
 COUNTER %= 1000.0F / float0;
 FRAME++;
 FRAME %= 56;
 }
 }
 }

 static void Reset() {
 TEXTURE = nullptr;
 }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
