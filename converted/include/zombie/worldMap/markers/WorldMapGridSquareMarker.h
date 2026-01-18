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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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

 WorldMapGridSquareMarker init(int int0, int int1, int int2, float float0, float float1, float float2, float float3) {
 this->m_worldX = int0;
 this->m_worldY = int1;
 this->m_radius = int2;
 this->m_r = float0;
 this->m_g = float1;
 this->m_b = float2;
 this->m_a = float3;
 return this;
 }

 void setBlink(bool blink) {
 this->m_blink = blink;
 }

 void setMinScreenRadius(int pixels) {
 this->m_minScreenRadius = pixels;
 }

 void render(UIWorldMap uIWorldMap) {
 float float0 = PZMath.max((float)this->m_radius, this->m_minScreenRadius / uIWorldMap.getAPI().getWorldScale());
 float float1 = uIWorldMap.getAPI().worldToUIX(this->m_worldX - float0, this->m_worldY - float0);
 float float2 = uIWorldMap.getAPI().worldToUIY(this->m_worldX - float0, this->m_worldY - float0);
 float float3 = uIWorldMap.getAPI().worldToUIX(this->m_worldX + float0, this->m_worldY - float0);
 float float4 = uIWorldMap.getAPI().worldToUIY(this->m_worldX + float0, this->m_worldY - float0);
 float float5 = uIWorldMap.getAPI().worldToUIX(this->m_worldX + float0, this->m_worldY + float0);
 float float6 = uIWorldMap.getAPI().worldToUIY(this->m_worldX + float0, this->m_worldY + float0);
 float float7 = uIWorldMap.getAPI().worldToUIX(this->m_worldX - float0, this->m_worldY + float0);
 float float8 = uIWorldMap.getAPI().worldToUIY(this->m_worldX - float0, this->m_worldY + float0);
 float1 = (float)(float1 + uIWorldMap.getAbsoluteX());
 float2 = (float)(float2 + uIWorldMap.getAbsoluteY());
 float3 = (float)(float3 + uIWorldMap.getAbsoluteX());
 float4 = (float)(float4 + uIWorldMap.getAbsoluteY());
 float5 = (float)(float5 + uIWorldMap.getAbsoluteX());
 float6 = (float)(float6 + uIWorldMap.getAbsoluteY());
 float7 = (float)(float7 + uIWorldMap.getAbsoluteX());
 float8 = (float)(float8 + uIWorldMap.getAbsoluteY());
 float float9 = this->m_a * (this->m_blink ? Core.blinkAlpha : 1.0F);
 if (this->m_texture1 != nullptr && this->m_texture1.isReady()) {
 SpriteRenderer.instance
 .render(this->m_texture1, float1, float2, float3, float4, float5, float6, float7, float8, this->m_r, this->m_g, this->m_b, float9, nullptr);
 }

 if (this->m_texture2 != nullptr && this->m_texture2.isReady()) {
 SpriteRenderer.instance
 .render(this->m_texture2, float1, float2, float3, float4, float5, float6, float7, float8, this->m_r, this->m_g, this->m_b, float9, nullptr);
 }
 }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
