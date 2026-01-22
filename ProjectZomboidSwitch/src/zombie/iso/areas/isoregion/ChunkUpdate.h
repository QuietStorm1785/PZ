#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include <filesystem>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class ChunkUpdate {
public:
    static void writeIsoChunkIntoBuffer(IsoChunk var0, ByteBuffer var1) {
      if (var0 != nullptr) {
    int var4 = var1.position();
         var1.putInt(0);
         var1.putInt(var0.maxLevel);
    int var5 = (var0.maxLevel + 1) * 100;
         var1.putInt(var5);

         for (int var6 = 0; var6 <= var0.maxLevel; var6++) {
            for (int var7 = 0; var7 < var0.squares[0].length; var7++) {
    IsoGridSquare var2 = var0.squares[var6][var7];
    uint8_t var3 = IsoRegions.calculateSquareFlags(var2);
               var1.put(var3);
            }
         }

    int var8 = var1.position();
         var1.position(var4);
         var1.putInt(var8 - var4);
         var1.position(var8);
      } else {
         var1.putInt(-1);
      }
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
