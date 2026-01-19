#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/Translator.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
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

class WorldMapTextSymbol : public WorldMapBaseSymbol {
public:
 std::string m_text;
 bool m_translated = false;
 UIFont m_font = UIFont.Handwritten;

public
 WorldMapTextSymbol(WorldMapSymbols owner) { super(owner); }

 void setTranslatedText(std::string_view text) {
 this->m_text = text;
 this->m_translated = true;
 if (!GameServer.bServer) {
 this->m_width = TextManager.instance.MeasureStringX(
 this->m_font, this->getTranslatedText());
 this->m_height = TextManager.instance.getFontHeight(this->m_font);
 }
 }

 void setUntranslatedText(std::string_view text) {
 this->m_text = text;
 this->m_translated = false;
 if (!GameServer.bServer) {
 this->m_width = TextManager.instance.MeasureStringX(
 this->m_font, this->getTranslatedText());
 this->m_height = TextManager.instance.getFontHeight(this->m_font);
 }
 }

 std::string getTranslatedText() {
 return this->m_translated ? this->m_text : Translator.getText(this->m_text);
 }

 std::string getUntranslatedText() {
 return this->m_translated ? nullptr : this->m_text;
 }

public
 WorldMapSymbols.WorldMapSymbolType getType() {
 return WorldMapSymbols.WorldMapSymbolType.Text;
 }

 bool isVisible() {
 return this->m_owner.getMiniMapSymbols() ? false : super.isVisible();
 }

 void save(ByteBuffer output) {
 super.save(output);
 GameWindow.WriteString(output, this->m_text);
 output.put((byte)(this->m_translated ? 1 : 0);
 }

 void load(ByteBuffer input, int WorldVersion, int SymbolsVersion) {
 super.load(input, WorldVersion, SymbolsVersion);
 this->m_text = GameWindow.ReadString(input);
 this->m_translated = input.get() == 1;
 }

 void render(UIWorldMap ui, float rox, float roy) {
 if (this->m_width == 0.0F || this->m_height == 0.0F) {
 this->m_width = TextManager.instance.MeasureStringX(
 this->m_font, this->getTranslatedText());
 this->m_height = TextManager.instance.getFontHeight(this->m_font);
 }

 if (this->m_collided) {
 this->renderCollided(ui, rox, roy);
 } else {
 float float0 = rox + this->m_layoutX;
 float float1 = roy + this->m_layoutY;
 if (this->m_scale > 0.0F) {
 ui.DrawText(this->m_font, this->getTranslatedText(), float0, float1,
 this->getDisplayScale(ui), this->m_r, this->m_g, this->m_b,
 this->m_a);
 } else {
 ui.DrawText(this->m_font, this->getTranslatedText(), float0, float1,
 this->m_r, this->m_g, this->m_b, this->m_a);
 }
 }
 }

 void release() { this->m_text = nullptr; }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
