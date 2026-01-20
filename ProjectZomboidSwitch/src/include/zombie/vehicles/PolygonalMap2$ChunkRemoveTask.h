#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/vehicles/PolygonalMap2/Cell.h"
#include "zombie/vehicles/PolygonalMap2/IChunkTask.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    int wx;
    int wy;
   static const ArrayDeque<PolygonalMap2$ChunkRemoveTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$ChunkRemoveTask() {
   }

   PolygonalMap2$ChunkRemoveTask init(PolygonalMap2 var1, IsoChunk var2) {
      this.map = var1;
      this.wx = var2.wx;
      this.wy = var2.wy;
    return this;
   }

    void execute() {
    Cell var1 = this.map.getCellFromChunkPos(this.wx, this.wy);
      var1.removeChunk(this.wx, this.wy);
   }

   static PolygonalMap2$ChunkRemoveTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$ChunkRemoveTask() : pool.pop();
      }
   }

    void release() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw std::make_unique<AssertionError>();
         } else {
            pool.push(this);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
