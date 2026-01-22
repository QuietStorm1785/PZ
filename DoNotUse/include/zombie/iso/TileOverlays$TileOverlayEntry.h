#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/TileOverlays/TileOverlayUsage.h"
#include "zombie/util/LocationRNG.h"

namespace zombie {
namespace iso {


class TileOverlays {
public:
    std::string room;
    int chance;
   public const std::vector<std::string> tiles = std::make_unique<std::vector<>>();
    const TileOverlayUsage usage = std::make_shared<TileOverlayUsage>();

   private TileOverlays$TileOverlayEntry() {
   }

    bool matchUsage(IsoGridSquare var1) {
      return this.usage.match(var1);
   }

    std::string pickRandom(int var1, int var2, int var3) {
    int var4 = LocationRNG.instance.nextInt(this.chance, var1, var2, var3);
      if (var4 == 0 && !this.tiles.empty()) {
         var4 = LocationRNG.instance.nextInt(this.tiles.size());
         return this.tiles.get(var4);
      } else {
    return nullptr;
      }
   }
}
} // namespace iso
} // namespace zombie
