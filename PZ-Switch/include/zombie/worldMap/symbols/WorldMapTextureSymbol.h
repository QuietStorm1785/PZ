#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace symbols {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapTextureSymbol : public WorldMapBaseSymbol {
public:
 std::string m_symbolID;
 Texture m_texture;

public
 WorldMapTextureSymbol(WorldMapSymbols owner) { super(owner); }

 void setSymbolID(std::string_view symbolID) { this->m_symbolID = symbolID; }

 std::string getSymbolID() { return this->m_symbolID; }

 void checkTexture() {
 if (this->m_texture.empty()) {
 MapSymbolDefinitions.MapSymbolDefinition mapSymbolDefinition =
 MapSymbolDefinitions.getInstance().getSymbolById(this->getSymbolID());
 if (mapSymbolDefinition.empty()) {
 this->m_width = 18.0F;
 this->m_height = 18.0F;
 } else {
 this->m_texture =
 Texture.getSharedTexture(mapSymbolDefinition.getTexturePath());
 this->m_width = mapSymbolDefinition.getWidth();
 this->m_height = mapSymbolDefinition.getHeight();
 }

 if (this->m_texture.empty()) {
 this->m_texture = Texture.getErrorTexture();
 }
 }
 }

public
 WorldMapSymbols.WorldMapSymbolType getType() {
 return WorldMapSymbols.WorldMapSymbolType.Texture;
 }

 void layout(UIWorldMap ui, WorldMapSymbolCollisions collisions, float rox,
 float roy) {
 this->checkTexture();
 super.layout(ui, collisions, rox, roy);
 }

 void save(ByteBuffer output) {
 super.save(output);
 GameWindow.WriteString(output, this->m_symbolID);
 }

 void load(ByteBuffer input, int WorldVersion, int SymbolsVersion) {
 super.load(input, WorldVersion, SymbolsVersion);
 this->m_symbolID = GameWindow.ReadString(input);
 }

 void render(UIWorldMap ui, float rox, float roy) {
 if (this->m_collided) {
 this->renderCollided(ui, rox, roy);
 } else {
 this->checkTexture();
 float float0 = rox + this->m_layoutX;
 float float1 = roy + this->m_layoutY;
 if (this->m_scale > 0.0F) {
 float float2 = this->getDisplayScale(ui);
 SpriteRenderer.instance.m_states.getPopulatingActiveState().render(
 this->m_texture, ui.getAbsoluteX().intValue() + float0,
 ui.getAbsoluteY().intValue() + float1,
 this->m_texture.getWidth() * float2,
 this->m_texture.getHeight() * float2, this->m_r, this->m_g, this->m_b,
 this->m_a, nullptr);
 } else {
 ui.DrawTextureColor(this->m_texture, float0, float1, this->m_r, this->m_g,
 this->m_b, this->m_a);
 }
 }
 }

 void release() {
 this->m_symbolID = nullptr;
 this->m_texture = nullptr;
 }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
