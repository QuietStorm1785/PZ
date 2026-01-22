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

    static void render(int var0, int var1, int var2) {
      if (TEXTURE == nullptr) {
         TEXTURE = Texture.getSharedTexture("media/textures/CorpseFlies.png");
      }

      if (TEXTURE != nullptr && TEXTURE.isReady()) {
    int var3 = (FRAME + var0 + var1) % 56;
    int var4 = var3 % 8;
    int var5 = var3 / 8;
    float var6 = (float)(var4 * 128) / TEXTURE.getWidth();
    float var7 = (float)(var5 * 128) / TEXTURE.getHeight();
    float var8 = (float)((var4 + 1) * 128) / TEXTURE.getWidth();
    float var9 = (float)((var5 + 1) * 128) / TEXTURE.getHeight();
    float var10 = IsoUtils.XToScreen(var0 + 0.5F, var1 + 0.5F, var2, 0) + IsoSprite.globalOffsetX;
    float var11 = IsoUtils.YToScreen(var0 + 0.5F, var1 + 0.5F, var2, 0) + IsoSprite.globalOffsetY;
    uint8_t var12 = 64;
    int var13 = var12 * Core.TileScale;
         var10 -= var13 / 2;
         var11 -= var13 + 16 * Core.TileScale;
         if (Core.bDebug) {
         }

         SpriteRenderer.instance.render(TEXTURE, var10, var11, var13, var13, 1.0F, 1.0F, 1.0F, 1.0F, var6, var7, var8, var7, var8, var9, var6, var9);
      }
   }

    static void update() {
      if (!GameServer.bServer) {
         COUNTER = COUNTER + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * 1000.0F;
    float var0 = 20.0F;
         if (COUNTER > 1000.0F / var0) {
            COUNTER %= 1000.0F / var0;
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
