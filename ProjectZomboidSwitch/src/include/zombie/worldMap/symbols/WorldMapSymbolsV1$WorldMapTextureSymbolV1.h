#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/symbols/WorldMapSymbolsV1/WorldMapBaseSymbolV1.h"

namespace zombie {
namespace worldMap {
namespace symbols {


class WorldMapSymbolsV1 {
public:
    WorldMapTextureSymbol m_textureSymbol;

   WorldMapSymbolsV1$WorldMapTextureSymbolV1 init(WorldMapSymbolsV1 var1, WorldMapTextureSymbol var2) {
      super.init(var1, var2);
      this.m_textureSymbol = var2;
    return this;
   }

    std::string getSymbolID() {
      return this.m_textureSymbol.getSymbolID();
   }

    bool isTexture() {
    return true;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
