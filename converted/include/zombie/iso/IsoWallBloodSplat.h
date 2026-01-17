#pragma once
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoWallBloodSplat {
public:
  static const ColorInfo info = new ColorInfo();
  float worldAge;
  IsoSprite sprite;

public
  IsoWallBloodSplat() {}

public
  IsoWallBloodSplat(float float0, IsoSprite spritex) {
    this.worldAge = float0;
    this.sprite = spritex;
  }

  void render(float float1, float float2, float float3, ColorInfo colorInfo) {
    if (this.sprite != nullptr) {
      if (this.sprite.CurrentAnim != nullptr &&
          !this.sprite.CurrentAnim.Frames.isEmpty()) {
        int int0 = Core.TileScale;
        int int1 = 32 * int0;
        int int2 = 96 * int0;
        if (IsoSprite.globalOffsetX == -1.0F) {
          IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
          IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
        }

        float float0 = IsoUtils.XToScreen(float1, float2, float3, 0);
        float float4 = IsoUtils.YToScreen(float1, float2, float3, 0);
        float0 -= int1;
        float4 -= int2;
        float0 += IsoSprite.globalOffsetX;
        float4 += IsoSprite.globalOffsetY;
        if (!(float0 >= IsoCamera.frameState.OffscreenWidth) &&
            !(float0 + 64 * int0 <= 0.0F)) {
          if (!(float4 >= IsoCamera.frameState.OffscreenHeight) &&
              !(float4 + 128 * int0 <= 0.0F)) {
            info.r = 0.7F * colorInfo.r;
            info.g = 0.9F * colorInfo.g;
            info.b = 0.9F * colorInfo.b;
            info.a = 0.4F;
            float float5 = (float)GameTime.getInstance().getWorldAgeHours();
            float float6 = float5 - this.worldAge;
            if (float6 >= 0.0F && float6 < 72.0F) {
              float float7 = 1.0F - float6 / 72.0F;
              info.r *= 0.2F + float7 * 0.8F;
              info.g *= 0.2F + float7 * 0.8F;
              info.b *= 0.2F + float7 * 0.8F;
              info.a *= 0.25F + float7 * 0.75F;
            } else {
              info.r *= 0.2F;
              info.g *= 0.2F;
              info.b *= 0.2F;
              info.a *= 0.25F;
            }

            info.a = Math.max(info.a, 0.15F);
            this.sprite.CurrentAnim.Frames.get(0).render(
                float0, float4, IsoDirections.N, info, false, nullptr);
          }
        }
      }
    }
  }

  void save(ByteBuffer byteBuffer) {
    byteBuffer.putFloat(this.worldAge);
    byteBuffer.putInt(this.sprite.ID);
  }

  void load(ByteBuffer byteBuffer, int var2) {
    this.worldAge = byteBuffer.getFloat();
    int int0 = byteBuffer.getInt();
    this.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, int0);
  }
}
} // namespace iso
} // namespace zombie
