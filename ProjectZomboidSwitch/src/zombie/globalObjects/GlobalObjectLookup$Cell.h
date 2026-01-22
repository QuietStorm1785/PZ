#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/globalObjects/GlobalObjectLookup/Chunk.h"
#include <algorithm>

namespace zombie {
namespace globalObjects {


class GlobalObjectLookup {
public:
    const int cx;
    const int cy;
   const Chunk[] chunks = new Chunk[900];

   GlobalObjectLookup$Cell(int var1, int var2) {
      this.cx = var1;
      this.cy = var2;
   }

    Chunk getChunkAt(int var1, int var2, bool var3) {
    int var4 = (var1 - this.cx * 300) / 10;
    int var5 = (var2 - this.cy * 300) / 10;
    int var6 = var4 + var5 * 30;
      if (this.chunks[var6] == nullptr && var3) {
         this.chunks[var6] = std::make_unique<Chunk>();
      }

      return this.chunks[var6];
   }

    Chunk getChunkForObject(GlobalObject var1, bool var2) {
      return this.getChunkAt(var1.x, var1.y, var2);
   }

    void addObject(GlobalObject var1) {
    Chunk var2 = this.getChunkForObject(var1, true);
      if (var2.objects.contains(var1)) {
         throw IllegalStateException("duplicate object");
      } else {
         var2.objects.push_back(var1);
      }
   }

    void removeObject(GlobalObject var1) {
    Chunk var2 = this.getChunkForObject(var1, false);
      if (var2 != nullptr && var2.objects.contains(var1)) {
         var2.objects.remove(var1);
      } else {
         throw IllegalStateException("chunk doesn't contain object");
      }
   }

    void Reset() {
      for (int var1 = 0; var1 < this.chunks.length; var1++) {
    Chunk var2 = this.chunks[var1];
         if (var2 != nullptr) {
            var2.Reset();
         }
      }

      Arrays.fill(this.chunks, nullptr);
   }
}
} // namespace globalObjects
} // namespace zombie
