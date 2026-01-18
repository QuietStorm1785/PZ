#include "zombie/worldMap/symbols/WorldMapTextSymbol.h"

namespace zombie {
namespace worldMap {
namespace symbols {

public WorldMapTextSymbol::WorldMapTextSymbol(WorldMapSymbols owner) {
 // TODO: Implement WorldMapTextSymbol
 return nullptr;
}

void WorldMapTextSymbol::setTranslatedText(const std::string& text) {
 // TODO: Implement setTranslatedText
}

void WorldMapTextSymbol::setUntranslatedText(const std::string& text) {
 // TODO: Implement setUntranslatedText
}

std::string WorldMapTextSymbol::getTranslatedText() {
 // TODO: Implement getTranslatedText
 return "";
}

std::string WorldMapTextSymbol::getUntranslatedText() {
 // TODO: Implement getUntranslatedText
 return "";
}

bool WorldMapTextSymbol::isVisible() {
 // TODO: Implement isVisible
 return false;
}

void WorldMapTextSymbol::save(ByteBuffer output) {
 // TODO: Implement save
}

void WorldMapTextSymbol::load(ByteBuffer input, int WorldVersion, int SymbolsVersion) {
 // TODO: Implement load
}

void WorldMapTextSymbol::render(UIWorldMap ui, float rox, float roy) {
 // TODO: Implement render
}

void WorldMapTextSymbol::release() {
 // TODO: Implement release
}

} // namespace symbols
} // namespace worldMap
} // namespace zombie
