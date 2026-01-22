#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {
namespace symbols {

enum class WorldMapSymbols {
   NONE(-1),
   Text(0),
   Texture(1);

    const uint8_t m_type;

   private WorldMapSymbols$WorldMapSymbolType(int var3) {
      this.m_type = (byte)var3;
   }

    int index() {
      return this.m_type;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
