#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include <filesystem>

namespace zombie {
namespace erosion {
namespace categories {


class WallCracks {
public:
    int gameObj;
    int spawnTime;
    int curID = -999999;
    float alpha;
   public WallCracks$CategoryData hasTop;

   private WallCracks$CategoryData() {
   }

    void save(ByteBuffer var1) {
      super.save(var1);
      var1.put((byte)this.gameObj);
      var1.putShort((short)this.spawnTime);
      var1.putInt(this.curID);
      var1.putFloat(this.alpha);
      if (this.hasTop != nullptr) {
         var1.put((byte)1);
         var1.put((byte)this.hasTop.gameObj);
         var1.putShort((short)this.hasTop.spawnTime);
         var1.putInt(this.hasTop.curID);
         var1.putFloat(this.hasTop.alpha);
      } else {
         var1.put((byte)0);
      }
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.gameObj = var1.get();
      this.spawnTime = var1.getShort();
      this.curID = var1.getInt();
      this.alpha = var1.getFloat();
    bool var3 = var1.get() == 1;
      if (var3) {
         this.hasTop = new WallCracks$CategoryData();
         this.hasTop.gameObj = var1.get();
         this.hasTop.spawnTime = var1.getShort();
         this.hasTop.curID = var1.getInt();
         this.hasTop.alpha = var1.getFloat();
      }
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
