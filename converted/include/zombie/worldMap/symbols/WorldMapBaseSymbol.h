#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace worldMap {
namespace symbols {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldMapBaseSymbol {
public:
 static float DEFAULT_SCALE = 0.666F;
 WorldMapSymbols m_owner;
 float m_x;
 float m_y;
 float m_width;
 float m_height;
 float m_anchorX = 0.0F;
 float m_anchorY = 0.0F;
 float m_scale = DEFAULT_SCALE;
 float m_r;
 float m_g;
 float m_b;
 float m_a;
 bool m_collide = false;
 bool m_collided = false;
 float m_layoutX;
 float m_layoutY;
 bool m_visible = true;

 public WorldMapBaseSymbol(WorldMapSymbols owner) {
 this->m_owner = owner;
 }

 public WorldMapSymbols.WorldMapSymbolType getType();

 void setAnchor(float x, float y) {
 this->m_anchorX = PZMath.clamp(x, 0.0F, 1.0F);
 this->m_anchorY = PZMath.clamp(y, 0.0F, 1.0F);
 }

 void setPosition(float x, float y) {
 this->m_x = x;
 this->m_y = y;
 }

 void setCollide(bool collide) {
 this->m_collide = collide;
 }

 void setRGBA(float r, float g, float b, float a) {
 this->m_r = PZMath.clamp_01(r);
 this->m_g = PZMath.clamp_01(g);
 this->m_b = PZMath.clamp_01(b);
 this->m_a = PZMath.clamp_01(a);
 }

 void setScale(float scale) {
 this->m_scale = scale;
 }

 float getDisplayScale(UIWorldMap ui) {
 if (this->m_scale <= 0.0F) {
 return this->m_scale;
 } else {
 return this->m_owner.getMiniMapSymbols() ? PZMath.min(this->m_owner.getLayoutWorldScale(), 1.0F) : this->m_owner.getLayoutWorldScale() * this->m_scale;
 }
 }

 void layout(UIWorldMap ui, WorldMapSymbolCollisions collisions, float rox, float roy) {
 float float0 = ui.getAPI().worldToUIX(this->m_x, this->m_y) - rox;
 float float1 = ui.getAPI().worldToUIY(this->m_x, this->m_y) - roy;
 this->m_layoutX = float0 - this->widthScaled(ui) * this->m_anchorX;
 this->m_layoutY = float1 - this->heightScaled(ui) * this->m_anchorY;
 this->m_collided = collisions.addBox(this->m_layoutX, this->m_layoutY, this->widthScaled(ui), this->heightScaled(ui), this->m_collide);
 if (this->m_collided) {
 }
 }

 float widthScaled(UIWorldMap ui) {
 return this->m_scale <= 0.0F ? this->m_width : this->m_width * this->getDisplayScale(ui);
 }

 float heightScaled(UIWorldMap ui) {
 return this->m_scale <= 0.0F ? this->m_height : this->m_height * this->getDisplayScale(ui);
 }

 void setVisible(bool visible) {
 this->m_visible = visible;
 }

 bool isVisible() {
 return this->m_visible;
 }

 void save(ByteBuffer output) {
 output.putFloat(this->m_x);
 output.putFloat(this->m_y);
 output.putFloat(this->m_anchorX);
 output.putFloat(this->m_anchorY);
 output.putFloat(this->m_scale);
 output.put((byte)(this->m_r * 255.0F);
 output.put((byte)(this->m_g * 255.0F);
 output.put((byte)(this->m_b * 255.0F);
 output.put((byte)(this->m_a * 255.0F);
 output.put((byte)(this->m_collide ? 1 : 0);
 }

 void load(ByteBuffer input, int WorldVersion, int SymbolsVersion) {
 this->m_x = input.getFloat();
 this->m_y = input.getFloat();
 this->m_anchorX = input.getFloat();
 this->m_anchorY = input.getFloat();
 this->m_scale = input.getFloat();
 this->m_r = (input.get() & 255) / 255.0F;
 this->m_g = (input.get() & 255) / 255.0F;
 this->m_b = (input.get() & 255) / 255.0F;
 this->m_a = (input.get() & 255) / 255.0F;
 this->m_collide = input.get() == 1;
 }

 public void render(UIWorldMap ui, float rox, float roy);

 void renderCollided(UIWorldMap uIWorldMap, float float1, float float3) {
 float float0 = float1 + this->m_layoutX + this->widthScaled(uIWorldMap) / 2.0F;
 float float2 = float3 + this->m_layoutY + this->heightScaled(uIWorldMap) / 2.0F;
 uIWorldMap.DrawTextureScaledCol(nullptr, float0 - 3.0F, float2 - 3.0F, 6.0, 6.0, this->m_r, this->m_g, this->m_b, this->m_a);
 }

 public void release();
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
