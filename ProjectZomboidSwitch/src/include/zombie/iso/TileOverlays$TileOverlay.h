#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/TileOverlays/TileOverlayEntry.h"
#include "zombie/util/LocationRNG.h"

namespace zombie {
namespace iso {


class TileOverlays {
public:
    std::string tile;
   public const std::vector<TileOverlayEntry> entries = std::make_unique<std::vector<>>();

   private TileOverlays$TileOverlay() {
   }

    void getEntries(const std::string& var1, IsoGridSquare var2, std::vector<TileOverlayEntry> var3) {
      var3.clear();

      for (int var4 = 0; var4 < this.entries.size(); var4++) {
    TileOverlayEntry var5 = this.entries.get(var4);
         if (var5.room.equalsIgnoreCase(var1) && var5.matchUsage(var2)) {
            var3.push_back(var5);
         }
      }
   }

    TileOverlayEntry pickRandom(const std::string& var1, IsoGridSquare var2) {
      this.getEntries(var1, var2, TileOverlays.tempEntries);
      if (TileOverlays.tempEntries.empty()) {
    return nullptr;
      } else {
    int var3 = LocationRNG.instance.nextInt(TileOverlays.tempEntries.size(), var2.x, var2.y, var2.z);
         return (TileOverlayEntry)TileOverlays.tempEntries.get(var3);
      }
   }
}
} // namespace iso
} // namespace zombie
