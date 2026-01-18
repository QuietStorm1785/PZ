#include "zombie/worldMap/symbols/WorldMapSymbols.h"

namespace zombie {
namespace worldMap {
namespace symbols {

WorldMapTextSymbol WorldMapSymbols::addTranslatedText(const std::string &text,
                                                      UIFont font, float x,
                                                      float y, float r, float g,
                                                      float b, float a) {
  // TODO: Implement addTranslatedText
  return nullptr;
}

WorldMapTextSymbol WorldMapSymbols::addUntranslatedText(const std::string &text,
                                                        UIFont font, float x,
                                                        float y, float r,
                                                        float g, float b,
                                                        float a) {
  // TODO: Implement addUntranslatedText
  return nullptr;
}

WorldMapTextureSymbol WorldMapSymbols::addTexture(const std::string &symbolID,
                                                  float x, float y, float r,
                                                  float g, float b, float a) {
  // TODO: Implement addTexture
  return nullptr;
}

WorldMapTextureSymbol WorldMapSymbols::addTexture(const std::string &symbolID,
                                                  float x, float y,
                                                  float anchorX, float anchorY,
                                                  float scale, float r, float g,
                                                  float b, float a) {
  // TODO: Implement addTexture
  return nullptr;
}

void WorldMapSymbols::removeSymbolByIndex(int index) {
  // TODO: Implement removeSymbolByIndex
}

void WorldMapSymbols::clear() {
  // TODO: Implement clear
}

void WorldMapSymbols::invalidateLayout() {
  // TODO: Implement invalidateLayout
}

void WorldMapSymbols::render(UIWorldMap ui) {
  // TODO: Implement render
}

void WorldMapSymbols::checkLayout(UIWorldMap uIWorldMap) {
  // TODO: Implement checkLayout
}

int WorldMapSymbols::getSymbolCount() {
  // TODO: Implement getSymbolCount
  return 0;
}

WorldMapBaseSymbol WorldMapSymbols::getSymbolByIndex(int index) {
  // TODO: Implement getSymbolByIndex
  return nullptr;
}

bool WorldMapSymbols::isSymbolVisible(UIWorldMap uIWorldMap,
                                      WorldMapBaseSymbol worldMapBaseSymbol) {
  // TODO: Implement isSymbolVisible
  return false;
}

int WorldMapSymbols::hitTest(UIWorldMap uIWorldMap, float float0,
                             float float1) {
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

void WorldMapSymbols::save(ByteBuffer output) {
  // TODO: Implement save
}

void WorldMapSymbols::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

private
WorldMapSymbols::WorldMapSymbolType(int int1) {
  // TODO: Implement WorldMapSymbolType
  return nullptr;
}

int WorldMapSymbols::index() {
  // TODO: Implement index
  return 0;
}

} // namespace symbols
} // namespace worldMap
} // namespace zombie
