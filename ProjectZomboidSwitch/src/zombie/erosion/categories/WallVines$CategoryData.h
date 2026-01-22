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


class WallVines {
public:
    int gameObj;
    int maxStage;
    int spawnTime;
    int curID = -999999;
   public WallVines$CategoryData hasTop;

   private WallVines$CategoryData() {
   }

    void save(ByteBuffer var1) {
      super.save(var1);
      var1.put((byte)this.gameObj);
      var1.put((byte)this.maxStage);
      var1.putShort((short)this.spawnTime);
      var1.putInt(this.curID);
      if (this.hasTop != nullptr) {
         var1.put((byte)1);
         var1.put((byte)this.hasTop.gameObj);
         var1.putShort((short)this.hasTop.spawnTime);
         var1.putInt(this.hasTop.curID);
      } else {
         var1.put((byte)0);
      }
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.gameObj = var1.get();
      this.maxStage = var1.get();
      this.spawnTime = var1.getShort();
      this.curID = var1.getInt();
    bool var3 = var1.get() == 1;
      if (var3) {
         this.hasTop = new WallVines$CategoryData();
         this.hasTop.gameObj = var1.get();
         this.hasTop.spawnTime = var1.getShort();
         this.hasTop.curID = var1.getInt();
      }
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
