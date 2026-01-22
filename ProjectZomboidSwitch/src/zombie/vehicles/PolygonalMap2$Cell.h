#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    short cx;
    short cy;
   public Chunk[][] chunks;
   static const ArrayDeque<PolygonalMap2$Cell> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$Cell() {
   }

   PolygonalMap2$Cell init(PolygonalMap2 var1, int var2, int var3) {
      this.map = var1;
      this.cx = (short)var2;
      this.cy = (short)var3;
    return this;
   }

    Chunk getChunkFromChunkPos(int var1, int var2) {
      if (this.chunks == nullptr) {
    return nullptr;
      } else {
         var1 -= this.cx * 30;
         var2 -= this.cy * 30;
         return var1 >= 0 && var1 < 30 && var2 >= 0 && var2 < 30 ? this.chunks[var1][var2] : nullptr;
      }
   }

    Chunk allocChunkIfNeeded(int var1, int var2) {
      var1 -= this.cx * 30;
      var2 -= this.cy * 30;
      if (var1 >= 0 && var1 < 30 && var2 >= 0 && var2 < 30) {
         if (this.chunks == nullptr) {
            this.chunks = new Chunk[30][30];
         }

         if (this.chunks[var1][var2] == nullptr) {
            this.chunks[var1][var2] = Chunk.alloc();
         }

         this.chunks[var1][var2].init(this.cx * 30 + var1, this.cy * 30 + var2);
         return this.chunks[var1][var2];
      } else {
    return nullptr;
      }
   }

    void removeChunk(int var1, int var2) {
      if (this.chunks != nullptr) {
         var1 -= this.cx * 30;
         var2 -= this.cy * 30;
         if (var1 >= 0 && var1 < 30 && var2 >= 0 && var2 < 30) {
    Chunk var3 = this.chunks[var1][var2];
            if (var3 != nullptr) {
               var3.release();
               this.chunks[var1][var2] = nullptr;
            }
         }
      }
   }

   static PolygonalMap2$Cell alloc() {
      return pool.empty() ? new PolygonalMap2$Cell() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
