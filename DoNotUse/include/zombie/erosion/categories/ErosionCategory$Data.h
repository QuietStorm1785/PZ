#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace erosion {
namespace categories {


class ErosionCategory {
public:
    int regionID;
    int categoryID;
    bool doNothing;
    bool hasSpawned;
    int stage;
    int dispSeason;
    bool dispBloom;

    void save(ByteBuffer var1) {
    uint8_t var2 = 0;
      if (this.doNothing) {
         var2 = (byte)(var2 | 1);
      }

      if (this.hasSpawned) {
         var2 = (byte)(var2 | 2);
      }

      if (this.dispBloom) {
         var2 = (byte)(var2 | 4);
      }

      if (this.stage == 1) {
         var2 = (byte)(var2 | 8);
      } else if (this.stage == 2) {
         var2 = (byte)(var2 | 16);
      } else if (this.stage == 3) {
         var2 = (byte)(var2 | 32);
      } else if (this.stage == 4) {
         var2 = (byte)(var2 | 64);
      } else if (this.stage > 4) {
         var2 = (byte)(var2 | 128);
      }

      var1.put((byte)this.regionID);
      var1.put((byte)this.categoryID);
      var1.put((byte)this.dispSeason);
      var1.put(var2);
      if (this.stage > 4) {
         var1.put((byte)this.stage);
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.stage = 0;
      this.dispSeason = var1.get();
    uint8_t var3 = var1.get();
      this.doNothing = (var3 & 1) != 0;
      this.hasSpawned = (var3 & 2) != 0;
      this.dispBloom = (var3 & 4) != 0;
      if ((var3 & 8) != 0) {
         this.stage = 1;
      } else if ((var3 & 16) != 0) {
         this.stage = 2;
      } else if ((var3 & 32) != 0) {
         this.stage = 3;
      } else if ((var3 & 64) != 0) {
         this.stage = 4;
      } else if ((var3 & 128) != 0) {
         this.stage = var1.get();
      }
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
