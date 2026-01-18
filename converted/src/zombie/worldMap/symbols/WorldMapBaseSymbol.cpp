#include "zombie/worldMap/symbols/WorldMapBaseSymbol.h"

namespace zombie {
namespace worldMap {
namespace symbols {

public WorldMapBaseSymbol::WorldMapBaseSymbol(WorldMapSymbols owner) {
 // TODO: Implement WorldMapBaseSymbol
 return nullptr;
}

void WorldMapBaseSymbol::setAnchor(float x, float y) {
 // TODO: Implement setAnchor
}

void WorldMapBaseSymbol::setPosition(float x, float y) {
 // TODO: Implement setPosition
}

void WorldMapBaseSymbol::setCollide(bool collide) {
 // TODO: Implement setCollide
}

void WorldMapBaseSymbol::setRGBA(float r, float g, float b, float a) {
 // TODO: Implement setRGBA
}

void WorldMapBaseSymbol::setScale(float scale) {
 // TODO: Implement setScale
}

float WorldMapBaseSymbol::getDisplayScale(UIWorldMap ui) {
 // TODO: Implement getDisplayScale
 return 0;
}

void WorldMapBaseSymbol::layout(UIWorldMap ui, WorldMapSymbolCollisions collisions, float rox, float roy) {
 // TODO: Implement layout
}

float WorldMapBaseSymbol::widthScaled(UIWorldMap ui) {
 // TODO: Implement widthScaled
 return 0;
}

float WorldMapBaseSymbol::heightScaled(UIWorldMap ui) {
 // TODO: Implement heightScaled
 return 0;
}

void WorldMapBaseSymbol::setVisible(bool visible) {
 // TODO: Implement setVisible
}

bool WorldMapBaseSymbol::isVisible() {
 // TODO: Implement isVisible
 return false;
}

void WorldMapBaseSymbol::save(ByteBuffer output) {
 // TODO: Implement save
}

void WorldMapBaseSymbol::load(ByteBuffer input, int WorldVersion, int SymbolsVersion) {
 // TODO: Implement load
}

void WorldMapBaseSymbol::renderCollided(UIWorldMap uIWorldMap, float float1, float float3) {
 // TODO: Implement renderCollided
}

} // namespace symbols
} // namespace worldMap
} // namespace zombie
