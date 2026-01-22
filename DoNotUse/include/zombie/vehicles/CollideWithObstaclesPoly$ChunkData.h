#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/ChunkDataZ.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
   const ChunkDataZ[] data = new ChunkDataZ[8];
    bool bClear = false;

    ChunkDataZ init(IsoChunk var1, int var2, CollideWithObstaclesPoly var3) {
      if (!$assertionsDisabled && Thread.currentThread() != GameWindow.GameThread) {
         throw std::make_unique<AssertionError>();
      } else {
         if (this.bClear) {
            this.bClear = false;
            this.clearInner();
         }

         if (this.data[var2] == nullptr) {
            this.data[var2] = (ChunkDataZ)ChunkDataZ.pool.alloc();
            this.data[var2].init(var1, var2, var3);
         }

         return this.data[var2];
      }
   }

    void clearInner() {
      PZArrayUtil.forEach(this.data, var0 -> {
         if (var0 != nullptr) {
            var0.clear();
            ChunkDataZ.pool.release(var0);
         }
      });
      Arrays.fill(this.data, nullptr);
   }

    void clear() {
      this.bClear = true;
   }
}
} // namespace vehicles
} // namespace zombie
