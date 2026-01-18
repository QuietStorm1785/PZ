#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <algorithm>
#include <cstdint>
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

class WorldMapSymbolsV1 {
public:
private
 static Pool<WorldMapSymbolsV1.WorldMapTextSymbolV1> s_textPool =
 new Pool<>(WorldMapSymbolsV1.WorldMapTextSymbolV1::new);
private
 static Pool<WorldMapSymbolsV1.WorldMapTextureSymbolV1> s_texturePool =
 new Pool<>(WorldMapSymbolsV1.WorldMapTextureSymbolV1::new);
 const UIWorldMap m_ui;
 const WorldMapSymbols m_uiSymbols;
private
 ArrayList<WorldMapSymbolsV1.WorldMapBaseSymbolV1> m_symbols =
 std::make_unique<ArrayList<>>();

public
 WorldMapSymbolsV1(UIWorldMap ui, WorldMapSymbols symbols) {
 Objects.requireNonNull(ui);
 this->m_ui = ui;
 this->m_uiSymbols = symbols;
 this->reinit();
 }

public
 WorldMapSymbolsV1.WorldMapTextSymbolV1
 addTranslatedText(String text, UIFont font, float x, float y) {
 WorldMapTextSymbol worldMapTextSymbol = this->m_uiSymbols.addTranslatedText(
 text, font, x, y, 1.0F, 1.0F, 1.0F, 1.0F);
 WorldMapSymbolsV1.WorldMapTextSymbolV1 worldMapTextSymbolV1 =
 s_textPool.alloc().init(this, worldMapTextSymbol);
 this->m_symbols.add(worldMapTextSymbolV1);
 return worldMapTextSymbolV1;
 }

public
 WorldMapSymbolsV1.WorldMapTextSymbolV1
 addUntranslatedText(String text, UIFont font, float x, float y) {
 WorldMapTextSymbol worldMapTextSymbol =
 this->m_uiSymbols.addUntranslatedText(text, font, x, y, 1.0F, 1.0F, 1.0F,
 1.0F);
 WorldMapSymbolsV1.WorldMapTextSymbolV1 worldMapTextSymbolV1 =
 s_textPool.alloc().init(this, worldMapTextSymbol);
 this->m_symbols.add(worldMapTextSymbolV1);
 return worldMapTextSymbolV1;
 }

public
 WorldMapSymbolsV1.WorldMapTextureSymbolV1 addTexture(String symbolID, float x,
 float y) {
 WorldMapTextureSymbol worldMapTextureSymbol =
 this->m_uiSymbols.addTexture(symbolID, x, y, 1.0F, 1.0F, 1.0F, 1.0F);
 WorldMapSymbolsV1.WorldMapTextureSymbolV1 worldMapTextureSymbolV1 =
 s_texturePool.alloc().init(this, worldMapTextureSymbol);
 this->m_symbols.add(worldMapTextureSymbolV1);
 return worldMapTextureSymbolV1;
 }

 int hitTest(float uiX, float uiY) {
 return this->m_uiSymbols.hitTest(this->m_ui, uiX, uiY);
 }

 int getSymbolCount() { return this->m_symbols.size(); }

public
 WorldMapSymbolsV1.WorldMapBaseSymbolV1 getSymbolByIndex(int index) {
 return this->m_symbols.get(index);
 }

 void removeSymbolByIndex(int index) {
 this->m_uiSymbols.removeSymbolByIndex(index);
 this->m_symbols.remove(index).release();
 }

 void clear() {
 this->m_uiSymbols.clear();
 this->reinit();
 }

 void reinit() {
 for (int int0 = 0; int0 < this->m_symbols.size(); int0++) {
 this->m_symbols.get(int0).release();
 }

 this->m_symbols.clear();

 for (int int1 = 0; int1 < this->m_uiSymbols.getSymbolCount(); int1++) {
 WorldMapBaseSymbol worldMapBaseSymbol =
 this->m_uiSymbols.getSymbolByIndex(int1);
 WorldMapTextSymbol worldMapTextSymbol =
 Type.tryCastTo(worldMapBaseSymbol, WorldMapTextSymbol.class);
 if (worldMapTextSymbol != nullptr) {
 WorldMapSymbolsV1.WorldMapTextSymbolV1 worldMapTextSymbolV1 =
 s_textPool.alloc().init(this, worldMapTextSymbol);
 this->m_symbols.add(worldMapTextSymbolV1);
 }

 WorldMapTextureSymbol worldMapTextureSymbol =
 Type.tryCastTo(worldMapBaseSymbol, WorldMapTextureSymbol.class);
 if (worldMapTextureSymbol != nullptr) {
 WorldMapSymbolsV1.WorldMapTextureSymbolV1 worldMapTextureSymbolV1 =
 s_texturePool.alloc().init(this, worldMapTextureSymbol);
 this->m_symbols.add(worldMapTextureSymbolV1);
 }
 }
 }

 static void setExposed(LuaManager.Exposer exposer) {
 exposer.setExposed(WorldMapSymbolsV1.class);
 exposer.setExposed(WorldMapSymbolsV1.WorldMapTextSymbolV1.class);
 exposer.setExposed(WorldMapSymbolsV1.WorldMapTextureSymbolV1.class);
 }

protected
 static class WorldMapBaseSymbolV1 extends PooledObject {
 WorldMapSymbolsV1 m_owner;
 WorldMapBaseSymbol m_symbol;

 WorldMapSymbolsV1.WorldMapBaseSymbolV1
 init(WorldMapSymbolsV1 worldMapSymbolsV1,
 WorldMapBaseSymbol worldMapBaseSymbol) {
 this->m_owner = worldMapSymbolsV1;
 this->m_symbol = worldMapBaseSymbol;
 return this;
 }

 float getWorldX() { return this->m_symbol.m_x; }

 float getWorldY() { return this->m_symbol.m_y; }

 float getDisplayX() {
 this->m_owner.m_uiSymbols.checkLayout(this->m_owner.m_ui);
 return this->m_symbol.m_layoutX +
 this->m_owner.m_ui.getAPIv1().worldOriginX();
 }

 float getDisplayY() {
 this->m_owner.m_uiSymbols.checkLayout(this->m_owner.m_ui);
 return this->m_symbol.m_layoutY +
 this->m_owner.m_ui.getAPIv1().worldOriginY();
 }

 float getDisplayWidth() {
 this->m_owner.m_uiSymbols.checkLayout(this->m_owner.m_ui);
 return this->m_symbol.widthScaled(this->m_owner.m_ui);
 }

 float getDisplayHeight() {
 this->m_owner.m_uiSymbols.checkLayout(this->m_owner.m_ui);
 return this->m_symbol.heightScaled(this->m_owner.m_ui);
 }

 void setAnchor(float arg0, float arg1) {
 this->m_symbol.setAnchor(arg0, arg1);
 }

 void setPosition(float arg0, float arg1) {
 this->m_symbol.setPosition(arg0, arg1);
 this->m_owner.m_uiSymbols.invalidateLayout();
 }

 void setCollide(bool arg0) { this->m_symbol.setCollide(arg0); }

 void setVisible(bool arg0) { this->m_symbol.setVisible(arg0); }

 bool isVisible() { return this->m_symbol.isVisible(); }

 void setRGBA(float arg0, float arg1, float arg2, float arg3) {
 this->m_symbol.setRGBA(arg0, arg1, arg2, arg3);
 }

 float getRed() { return this->m_symbol.m_r; }

 float getGreen() { return this->m_symbol.m_g; }

 float getBlue() { return this->m_symbol.m_b; }

 float getAlpha() { return this->m_symbol.m_a; }

 void setScale(float arg0) { this->m_symbol.setScale(arg0); }

 bool isText() { return false; }

 bool isTexture() { return false; }
 }

 public static class WorldMapTextSymbolV1 extends
 WorldMapSymbolsV1.WorldMapBaseSymbolV1 {
 WorldMapTextSymbol m_textSymbol;

 WorldMapSymbolsV1.WorldMapTextSymbolV1 init(
 WorldMapSymbolsV1 worldMapSymbolsV1,
 WorldMapTextSymbol worldMapTextSymbol) {
 super.init(worldMapSymbolsV1, worldMapTextSymbol);
 this->m_textSymbol = worldMapTextSymbol;
 return this;
 }

 void setTranslatedText(const std::string &text) {
 if (!StringUtils.isNullOrWhitespace(text) {
 this->m_textSymbol.setTranslatedText(text);
 this->m_owner.m_uiSymbols.invalidateLayout();
 }
 }

 void setUntranslatedText(const std::string &text) {
 if (!StringUtils.isNullOrWhitespace(text) {
 this->m_textSymbol.setUntranslatedText(text);
 this->m_owner.m_uiSymbols.invalidateLayout();
 }
 }

 std::string getTranslatedText() {
 return this->m_textSymbol.getTranslatedText();
 }

 std::string getUntranslatedText() {
 return this->m_textSymbol.getUntranslatedText();
 }

 bool isText() { return true; }
 }

public
 static class WorldMapTextureSymbolV1 extends
 WorldMapSymbolsV1.WorldMapBaseSymbolV1 {
 WorldMapTextureSymbol m_textureSymbol;

 WorldMapSymbolsV1.WorldMapTextureSymbolV1 init(
 WorldMapSymbolsV1 worldMapSymbolsV1,
 WorldMapTextureSymbol worldMapTextureSymbol) {
 super.init(worldMapSymbolsV1, worldMapTextureSymbol);
 this->m_textureSymbol = worldMapTextureSymbol;
 return this;
 }

 std::string getSymbolID() { return this->m_textureSymbol.getSymbolID(); }

 bool isTexture() { return true; }
 }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
