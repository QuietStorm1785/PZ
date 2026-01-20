#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include "zombie/vehicles/PolygonalMap2/IChunkTask.h"
#include "zombie/vehicles/PolygonalMap2/SquareUpdateTask.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    int wx;
    int wy;
   const int[][][] data = new int[10][10][8];
   const short[][][] cost = new short[10][10][8];
   static const ArrayDeque<PolygonalMap2$ChunkUpdateTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$ChunkUpdateTask() {
   }

   PolygonalMap2$ChunkUpdateTask init(PolygonalMap2 var1, IsoChunk var2) {
      this.map = var1;
      this.wx = var2.wx;
      this.wy = var2.wy;

      for (int var3 = 0; var3 < 8; var3++) {
         for (int var4 = 0; var4 < 10; var4++) {
            for (int var5 = 0; var5 < 10; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var5, var4, var3);
               if (var6 == nullptr) {
                  this.data[var5][var4][var3] = 0;
                  this.cost[var5][var4][var3] = 0;
               } else {
                  this.data[var5][var4][var3] = SquareUpdateTask.getBits(var6);
                  this.cost[var5][var4][var3] = SquareUpdateTask.getCost(var6);
               }
            }
         }
      }

    return this;
   }

    void execute() {
    Chunk var1 = this.map.allocChunkIfNeeded(this.wx, this.wy);
      var1.setData(this);
   }

   static PolygonalMap2$ChunkUpdateTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$ChunkUpdateTask() : pool.pop();
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
