#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/UIWorldMap.h"

namespace zombie {
namespace worldMap {
namespace markers {


class WorldMapGridSquareMarker : public WorldMapMarker {
public:
    Texture m_texture1 = Texture.getSharedTexture("media/textures/worldMap/circle_center.png");
    Texture m_texture2 = Texture.getSharedTexture("media/textures/worldMap/circle_only_highlight.png");
    float m_r = 1.0F;
    float m_g = 1.0F;
    float m_b = 1.0F;
    float m_a = 1.0F;
    int m_worldX;
    int m_worldY;
    int m_radius = 10;
    int m_minScreenRadius = 64;
    bool m_blink = true;

    WorldMapGridSquareMarker init(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
      this.m_worldX = var1;
      this.m_worldY = var2;
      this.m_radius = var3;
      this.m_r = var4;
      this.m_g = var5;
      this.m_b = var6;
      this.m_a = var7;
    return this;
   }

    void setBlink(bool var1) {
      this.m_blink = var1;
   }

    void setMinScreenRadius(int var1) {
      this.m_minScreenRadius = var1;
   }

    void render(UIWorldMap var1) {
    float var2 = PZMath.max(this.m_radius, this.m_minScreenRadius / var1.getAPI().getWorldScale());
    float var3 = var1.getAPI().worldToUIX(this.m_worldX - var2, this.m_worldY - var2);
    float var4 = var1.getAPI().worldToUIY(this.m_worldX - var2, this.m_worldY - var2);
    float var5 = var1.getAPI().worldToUIX(this.m_worldX + var2, this.m_worldY - var2);
    float var6 = var1.getAPI().worldToUIY(this.m_worldX + var2, this.m_worldY - var2);
    float var7 = var1.getAPI().worldToUIX(this.m_worldX + var2, this.m_worldY + var2);
    float var8 = var1.getAPI().worldToUIY(this.m_worldX + var2, this.m_worldY + var2);
    float var9 = var1.getAPI().worldToUIX(this.m_worldX - var2, this.m_worldY + var2);
    float var10 = var1.getAPI().worldToUIY(this.m_worldX - var2, this.m_worldY + var2);
      var3 = (float)(var3 + var1.getAbsoluteX());
      var4 = (float)(var4 + var1.getAbsoluteY());
      var5 = (float)(var5 + var1.getAbsoluteX());
      var6 = (float)(var6 + var1.getAbsoluteY());
      var7 = (float)(var7 + var1.getAbsoluteX());
      var8 = (float)(var8 + var1.getAbsoluteY());
      var9 = (float)(var9 + var1.getAbsoluteX());
      var10 = (float)(var10 + var1.getAbsoluteY());
    float var11 = this.m_a * (this.m_blink ? Core.blinkAlpha : 1.0F);
      if (this.m_texture1 != nullptr && this.m_texture1.isReady()) {
         SpriteRenderer.instance.render(this.m_texture1, var3, var4, var5, var6, var7, var8, var9, var10, this.m_r, this.m_g, this.m_b, var11, nullptr);
      }

      if (this.m_texture2 != nullptr && this.m_texture2.isReady()) {
         SpriteRenderer.instance.render(this.m_texture2, var3, var4, var5, var6, var7, var8, var9, var10, this.m_r, this.m_g, this.m_b, var11, nullptr);
      }
   }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
