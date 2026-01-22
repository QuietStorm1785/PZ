#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include "zombie/vehicles/PolygonalMap2/ChunkDataZ.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
   const ChunkDataZ[] data = new ChunkDataZ[8];

   private PolygonalMap2$ChunkData() {
   }

    ChunkDataZ init(Chunk var1, int var2) {
      if (this.data[var2] == nullptr) {
         this.data[var2] = (ChunkDataZ)ChunkDataZ.pool.alloc();
         this.data[var2].init(var1, var2);
      } else if (this.data[var2].epoch != ChunkDataZ.EPOCH) {
         this.data[var2].clear();
         this.data[var2].init(var1, var2);
      }

      return this.data[var2];
   }

    void clear() {
      PZArrayUtil.forEach(this.data, var0 -> {
         if (var0 != nullptr) {
            var0.clear();
            ChunkDataZ.pool.release(var0);
         }
      });
      Arrays.fill(this.data, nullptr);
   }
}
} // namespace vehicles
} // namespace zombie
