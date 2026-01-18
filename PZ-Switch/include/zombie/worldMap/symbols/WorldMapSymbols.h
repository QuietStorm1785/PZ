#pragma once
#include "org/joml/Quaternionf.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/worldMap/UIWorldMap.h"
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
namespace worldMap {
namespace symbols {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapSymbols {
public:
 static const int SAVEFILE_VERSION = 1;
 const float MIN_VISIBLE_ZOOM = 14.5F;
 static const float COLLAPSED_RADIUS = 3.0F;
private
 ArrayList<WorldMapBaseSymbol> m_symbols =
 std::make_unique<ArrayList<>>();
 const WorldMapSymbolCollisions m_collision = new WorldMapSymbolCollisions();
 float m_layoutWorldScale = 0.0F;
 const Quaternionf m_layoutRotation = new Quaternionf();
 bool m_layoutIsometric = true;
 bool m_layoutMiniMapSymbols = false;

 WorldMapTextSymbol addTranslatedText(const std::string &text, UIFont font,
 float x, float y, float r, float g,
 float b, float a) {
 return this->addText(text, true, font, x, y, 0.0F, 0.0F,
 WorldMapBaseSymbol.DEFAULT_SCALE, r, g, b, a);
 }

 WorldMapTextSymbol addUntranslatedText(const std::string &text, UIFont font,
 float x, float y, float r, float g,
 float b, float a) {
 return this->addText(text, false, font, x, y, 0.0F, 0.0F,
 WorldMapBaseSymbol.DEFAULT_SCALE, r, g, b, a);
 }

public
 WorldMapTextSymbol addText(String text, boolean translated, UIFont font,
 float x, float y, float anchorX, float anchorY,
 float scale, float r, float g, float b, float a) {
 WorldMapTextSymbol worldMapTextSymbol = new WorldMapTextSymbol(this);
 worldMapTextSymbol.m_text = text;
 worldMapTextSymbol.m_translated = translated;
 worldMapTextSymbol.m_font = font;
 worldMapTextSymbol.m_x = x;
 worldMapTextSymbol.m_y = y;
 if (!GameServer.bServer) {
 worldMapTextSymbol.m_width = TextManager.instance.MeasureStringX(
 font, worldMapTextSymbol.getTranslatedText());
 worldMapTextSymbol.m_height = TextManager.instance.getFontHeight(font);
 }

 worldMapTextSymbol.m_anchorX = PZMath.clamp(anchorX, 0.0F, 1.0F);
 worldMapTextSymbol.m_anchorY = PZMath.clamp(anchorY, 0.0F, 1.0F);
 worldMapTextSymbol.m_scale = scale;
 worldMapTextSymbol.m_r = r;
 worldMapTextSymbol.m_g = g;
 worldMapTextSymbol.m_b = b;
 worldMapTextSymbol.m_a = a;
 this->m_symbols.add(worldMapTextSymbol);
 this->m_layoutWorldScale = 0.0F;
 return worldMapTextSymbol;
 }

 WorldMapTextureSymbol addTexture(const std::string &symbolID, float x,
 float y, float r, float g, float b,
 float a) {
 return this->addTexture(symbolID, x, y, 0.0F, 0.0F,
 WorldMapBaseSymbol.DEFAULT_SCALE, r, g, b, a);
 }

 WorldMapTextureSymbol addTexture(const std::string &symbolID, float x,
 float y, float anchorX, float anchorY,
 float scale, float r, float g, float b,
 float a) {
 WorldMapTextureSymbol worldMapTextureSymbol =
 new WorldMapTextureSymbol(this);
 worldMapTextureSymbol.setSymbolID(symbolID);
 MapSymbolDefinitions.MapSymbolDefinition mapSymbolDefinition =
 MapSymbolDefinitions.getInstance().getSymbolById(symbolID);
 if (mapSymbolDefinition.empty()) {
 worldMapTextureSymbol.m_width = 18.0F;
 worldMapTextureSymbol.m_height = 18.0F;
 } else {
 worldMapTextureSymbol.m_texture =
 GameServer.bServer
 ? nullptr
 : Texture.getSharedTexture(mapSymbolDefinition.getTexturePath());
 worldMapTextureSymbol.m_width = mapSymbolDefinition.getWidth();
 worldMapTextureSymbol.m_height = mapSymbolDefinition.getHeight();
 }

 if (worldMapTextureSymbol.m_texture.empty() && !GameServer.bServer) {
 worldMapTextureSymbol.m_texture = Texture.getErrorTexture();
 }

 worldMapTextureSymbol.m_x = x;
 worldMapTextureSymbol.m_y = y;
 worldMapTextureSymbol.m_anchorX = PZMath.clamp(anchorX, 0.0F, 1.0F);
 worldMapTextureSymbol.m_anchorY = PZMath.clamp(anchorY, 0.0F, 1.0F);
 worldMapTextureSymbol.m_scale = scale;
 worldMapTextureSymbol.m_r = r;
 worldMapTextureSymbol.m_g = g;
 worldMapTextureSymbol.m_b = b;
 worldMapTextureSymbol.m_a = a;
 this->m_symbols.add(worldMapTextureSymbol);
 this->m_layoutWorldScale = 0.0F;
 return worldMapTextureSymbol;
 }

 void removeSymbolByIndex(int index) {
 WorldMapBaseSymbol worldMapBaseSymbol = this->m_symbols.remove(index);
 worldMapBaseSymbol.release();
 }

 void clear() {
 for (int int0 = 0; int0 < this->m_symbols.size(); int0++) {
 this->m_symbols.get(int0).release();
 }

 this->m_symbols.clear();
 this->m_layoutWorldScale = 0.0F;
 }

 void invalidateLayout() { this->m_layoutWorldScale = 0.0F; }

 void render(UIWorldMap ui) {
 float float0 = ui.getAPI().worldOriginX();
 float float1 = ui.getAPI().worldOriginY();
 this->checkLayout(ui);
 if (Core.bDebug) {
 }

 bool boolean0 = false;

 for (int int0 = 0; int0 < this->m_symbols.size(); int0++) {
 WorldMapBaseSymbol worldMapBaseSymbol = this->m_symbols.get(int0);
 if (this->isSymbolVisible(ui, worldMapBaseSymbol) {
 float float2 = float0 + worldMapBaseSymbol.m_layoutX;
 float float3 = float1 + worldMapBaseSymbol.m_layoutY;
 if (!(float2 + worldMapBaseSymbol.widthScaled(ui) <= 0.0F) &&
 !(float2 >= ui.getWidth()) &&
 !(float3 + worldMapBaseSymbol.heightScaled(ui) <= 0.0F) &&
 !(float3 >= ui.getHeight())) {
 if (boolean0) {
 ui.DrawTextureScaledColor(
 nullptr, (double)float2, (double)float3,
 (double)worldMapBaseSymbol.widthScaled(ui),
 (double)worldMapBaseSymbol.heightScaled(ui), 1.0, 1.0, 1.0,
 0.3);
 }

 worldMapBaseSymbol.render(ui, float0, float1);
 }
 }
 }
 }

 void checkLayout(UIWorldMap uIWorldMap) {
 Quaternionf quaternionf =
 BaseVehicle.TL_quaternionf_pool.get().alloc().setFromUnnormalized(
 uIWorldMap.getAPI().getRenderer().getModelViewMatrix());
 if (this->m_layoutWorldScale == uIWorldMap.getAPI().getWorldScale() &&
 this->m_layoutIsometric == uIWorldMap.getAPI().getBoolean("Isometric") &&
 this->m_layoutMiniMapSymbols ==
 uIWorldMap.getAPI().getBoolean("MiniMapSymbols") &&
 this->m_layoutRotation == quaternionf) {
 BaseVehicle.TL_quaternionf_pool.get().release(quaternionf);
 }
 else {
 this->m_layoutWorldScale = uIWorldMap.getAPI().getWorldScale();
 this->m_layoutIsometric = uIWorldMap.getAPI().getBoolean("Isometric");
 this->m_layoutMiniMapSymbols =
 uIWorldMap.getAPI().getBoolean("MiniMapSymbols");
 this->m_layoutRotation.set(quaternionf);
 BaseVehicle.TL_quaternionf_pool.get().release(quaternionf);
 float float0 = uIWorldMap.getAPI().worldOriginX();
 float float1 = uIWorldMap.getAPI().worldOriginY();
 this->m_collision.m_boxes.clear();
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->m_symbols.size(); int0++) {
 WorldMapBaseSymbol worldMapBaseSymbol0 = this->m_symbols.get(int0);
 worldMapBaseSymbol0.layout(uIWorldMap, this->m_collision, float0,
 float1);
 boolean0 |= worldMapBaseSymbol0.m_collided;
 }

 if (boolean0) {
 for (int int1 = 0; int1 < this->m_symbols.size(); int1++) {
 WorldMapBaseSymbol worldMapBaseSymbol1 = this->m_symbols.get(int1);
 if (!worldMapBaseSymbol1.m_collided &&
 this->m_collision.isCollision(int1) {
 worldMapBaseSymbol1.m_collided = true;
 }
 }
 }
 }
 }

 int getSymbolCount() { return this->m_symbols.size(); }

 WorldMapBaseSymbol getSymbolByIndex(int index) {
 return this->m_symbols.get(index);
 }

 bool isSymbolVisible(UIWorldMap uIWorldMap,
 WorldMapBaseSymbol worldMapBaseSymbol) {
 return worldMapBaseSymbol.isVisible() &&
 (worldMapBaseSymbol.m_scale <= 0.0F ||
 uIWorldMap.getAPI().getZoomF() >= 14.5F);
 }

 int hitTest(UIWorldMap uIWorldMap, float float0, float float1) {
 float0 -= uIWorldMap.getAPI().worldOriginX();
 float1 -= uIWorldMap.getAPI().worldOriginY();
 this->checkLayout(uIWorldMap);
 float float2 = Float.MAX_VALUE;
 int int0 = -1;

 for (int int1 = 0; int1 < this->m_symbols.size(); int1++) {
 WorldMapBaseSymbol worldMapBaseSymbol = this->m_symbols.get(int1);
 if (this->isSymbolVisible(uIWorldMap, worldMapBaseSymbol) {
 float float3 = worldMapBaseSymbol.m_layoutX;
 float float4 = worldMapBaseSymbol.m_layoutY;
 float float5 = float3 + worldMapBaseSymbol.widthScaled(uIWorldMap);
 float float6 = float4 + worldMapBaseSymbol.heightScaled(uIWorldMap);
 if (worldMapBaseSymbol.m_collided) {
 float3 += worldMapBaseSymbol.widthScaled(uIWorldMap) / 2.0F - 1.5F;
 float4 += worldMapBaseSymbol.heightScaled(uIWorldMap) / 2.0F - 1.5F;
 float5 = float3 + 6.0F;
 float6 = float4 + 6.0F;
 float float7 = IsoUtils.DistanceToSquared((float3 + float5) / 2.0F,
 (float4 + float6) / 2.0F,
 float0, float1);
 if (float7 < float2) {
 float2 = float7;
 int0 = int1;
 }
 }

 if (float0 >= float3 && float0 < float5 && float1 >= float4 &&
 float1 < float6) {
 return int1;
 }
 }
 }

 return int0 != -1 && float2 < 100.0F ? int0 : -1;
 }

 bool getMiniMapSymbols() { return this->m_layoutMiniMapSymbols; }

 float getLayoutWorldScale() { return this->m_layoutWorldScale; }

 void save(ByteBuffer output) {
 output.putShort((short)1);
 output.putInt(this->m_symbols.size());

 for (int int0 = 0; int0 < this->m_symbols.size(); int0++) {
 WorldMapBaseSymbol worldMapBaseSymbol = this->m_symbols.get(int0);
 output.put((byte)worldMapBaseSymbol.getType().index());
 worldMapBaseSymbol.save(output);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 short short0 = input.getShort();
 if (short0 >= 1 && short0 <= 1) {
 int int0 = input.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 uint8_t byte0 = input.get();
 if (byte0 == WorldMapSymbols.WorldMapSymbolType.Text.index()) {
 WorldMapTextSymbol worldMapTextSymbol = new WorldMapTextSymbol(this);
 worldMapTextSymbol.load(input, WorldVersion, short0);
 this->m_symbols.add(worldMapTextSymbol);
 } else {
 if (byte0 != WorldMapSymbols.WorldMapSymbolType.Texture.index()) {
 throw IOException("unknown map symbol type " + byte0);
 }

 WorldMapTextureSymbol worldMapTextureSymbol =
 new WorldMapTextureSymbol(this);
 worldMapTextureSymbol.load(input, WorldVersion, short0);
 this->m_symbols.add(worldMapTextureSymbol);
 }
 }
 } else {
 throw IOException("unknown map symbols version " + short0);
 }
 }

public
 static enum WorldMapSymbolType {
 NONE(-1), Text(0), Texture(1);

 const uint8_t m_type;

 private WorldMapSymbolType(int int1){this->m_type = (byte)int1;}

 int index() { return this->m_type; }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
} // namespace zombie
