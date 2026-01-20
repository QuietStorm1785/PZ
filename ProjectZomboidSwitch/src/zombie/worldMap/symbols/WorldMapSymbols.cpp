#include <string>
#include "zombie\worldMap\symbols/WorldMapSymbols.h"

namespace zombie {
namespace worldMap {
namespace symbols {

WorldMapTextSymbol WorldMapSymbols::addTranslatedText(const std::string& var1, UIFont var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    // TODO: Implement addTranslatedText
    return nullptr;
}

WorldMapTextSymbol WorldMapSymbols::addUntranslatedText(const std::string& var1, UIFont var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    // TODO: Implement addUntranslatedText
    return nullptr;
}

WorldMapTextureSymbol WorldMapSymbols::addTexture(const std::string& var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    // TODO: Implement addTexture
    return nullptr;
}

void WorldMapSymbols::removeSymbolByIndex(int var1) {
    // TODO: Implement removeSymbolByIndex
}

void WorldMapSymbols::clear() {
    // TODO: Implement clear
}

void WorldMapSymbols::invalidateLayout() {
    // TODO: Implement invalidateLayout
}

void WorldMapSymbols::render(UIWorldMap var1) {
    // TODO: Implement render
}

void WorldMapSymbols::checkLayout(UIWorldMap var1) {
    // TODO: Implement checkLayout
}

int WorldMapSymbols::getSymbolCount() {
    // TODO: Implement getSymbolCount
    return 0;
}

WorldMapBaseSymbol WorldMapSymbols::getSymbolByIndex(int var1) {
    // TODO: Implement getSymbolByIndex
    return nullptr;
}

bool WorldMapSymbols::isSymbolVisible(UIWorldMap var1, WorldMapBaseSymbol var2) {
    // TODO: Implement isSymbolVisible
    return false;
}

int WorldMapSymbols::hitTest(UIWorldMap var1, float var2, float var3) {
    // TODO: Implement hitTest
    return 0;
}

bool WorldMapSymbols::getMiniMapSymbols() {
    // TODO: Implement getMiniMapSymbols
    return false;
}

float WorldMapSymbols::getLayoutWorldScale() {
    // TODO: Implement getLayoutWorldScale
    return 0;
}

void WorldMapSymbols::save(ByteBuffer var1) {
    // TODO: Implement save
}

void WorldMapSymbols::load(ByteBuffer var1, int var2) {
    // TODO: Implement load
}

} // namespace symbols
} // namespace worldMap
} // namespace zombie
