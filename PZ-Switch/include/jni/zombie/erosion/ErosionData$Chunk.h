#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include <filesystem>

namespace zombie {
namespace erosion {


class ErosionData {
:
    bool init = false;
    int eTickStamp = -1;
    int epoch = -1;
    int x;
    int y;
    float moisture;
    float minerals;
    int soil;

    void set(IsoChunk var1) {
      this.x = var1.wx;
      this.y = var1.wy;
   }

    void save(ByteBuffer var1) {
      if (this.init) {
         var1.put((byte)1);
         var1.putInt(this.eTickStamp);
         var1.putInt(this.epoch);
         var1.putFloat(this.moisture);
         var1.putFloat(this.minerals);
         var1.put((byte)this.soil);
      } else {
         var1.put((byte)0);
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.init = var1.get() == 1;
      if (this.init) {
         this.eTickStamp = var1.getInt();
         this.epoch = var1.getInt();
         this.moisture = var1.getFloat();
         this.minerals = var1.getFloat();
         this.soil = var1.get();
      }
   }
}
} // namespace erosion
} // namespace zombie
