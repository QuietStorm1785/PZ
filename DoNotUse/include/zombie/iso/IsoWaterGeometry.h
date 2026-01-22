#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/list/PZArrayList.h"

namespace zombie {
namespace iso {


class IsoWaterGeometry {
public:
    static const Vector2f tempVector2f = std::make_shared<Vector2f>();
    bool hasWater = false;
    bool bShore = false;
   const float[] x = new float[4];
   const float[] y = new float[4];
   const float[] depth = new float[4];
   const float[] flow = new float[4];
   const float[] speed = new float[4];
    float IsExternal = 0.0F;
    IsoGridSquare square = nullptr;
    int m_adjacentChunkLoadedCounter;
   public static const ObjectPool<IsoWaterGeometry> pool = std::make_shared<ObjectPool>(IsoWaterGeometry::new);

    IsoWaterGeometry init(IsoGridSquare var1) {
      this.x[0] = IsoUtils.XToScreen(var1.x, var1.y, 0.0F, 0);
      this.y[0] = IsoUtils.YToScreen(var1.x, var1.y, 0.0F, 0);
      this.x[1] = IsoUtils.XToScreen(var1.x, var1.y + 1, 0.0F, 0);
      this.y[1] = IsoUtils.YToScreen(var1.x, var1.y + 1, 0.0F, 0);
      this.x[2] = IsoUtils.XToScreen(var1.x + 1, var1.y + 1, 0.0F, 0);
      this.y[2] = IsoUtils.YToScreen(var1.x + 1, var1.y + 1, 0.0F, 0);
      this.x[3] = IsoUtils.XToScreen(var1.x + 1, var1.y, 0.0F, 0);
      this.y[3] = IsoUtils.YToScreen(var1.x + 1, var1.y, 0.0F, 0);
      this.hasWater = false;
      this.bShore = false;
      this.square = var1;
      this.IsExternal = var1.getProperties().Is(IsoFlagType.exterior) ? 1.0F : 0.0F;
    int var2 = IsoWaterFlow.getShore(var1.x, var1.y);
    IsoObject var3 = var1.getFloor();
    std::string var4 = var3 == nullptr ? nullptr : var3.getSprite().getName();
      if (var1.getProperties().Is(IsoFlagType.water)) {
         this.hasWater = true;

         for (int var14 = 0; var14 < 4; var14++) {
            this.depth[var14] = 1.0F;
         }
      } else if (var2 == 1 && var4 != nullptr && var4.startsWith("blends_natural")) {
         for (int var5 = 0; var5 < 4; var5++) {
            this.depth[var5] = 0.0F;
         }

    IsoGridSquare var13 = var1.getAdjacentSquare(IsoDirections.W);
    IsoGridSquare var6 = var1.getAdjacentSquare(IsoDirections.NW);
    IsoGridSquare var7 = var1.getAdjacentSquare(IsoDirections.N);
    IsoGridSquare var8 = var1.getAdjacentSquare(IsoDirections.SW);
    IsoGridSquare var9 = var1.getAdjacentSquare(IsoDirections.S);
    IsoGridSquare var10 = var1.getAdjacentSquare(IsoDirections.SE);
    IsoGridSquare var11 = var1.getAdjacentSquare(IsoDirections.E);
    IsoGridSquare var12 = var1.getAdjacentSquare(IsoDirections.NE);
         if (var7 == nullptr || var6 == nullptr || var13 == nullptr || var8 == nullptr || var9 == nullptr || var10 == nullptr || var11 == nullptr || var12 == nullptr) {
    return nullptr;
         }

         if (var13.getProperties().Is(IsoFlagType.water) || var6.getProperties().Is(IsoFlagType.water) || var7.getProperties().Is(IsoFlagType.water)) {
            this.bShore = true;
            this.depth[0] = 1.0F;
         }

         if (var13.getProperties().Is(IsoFlagType.water) || var8.getProperties().Is(IsoFlagType.water) || var9.getProperties().Is(IsoFlagType.water)) {
            this.bShore = true;
            this.depth[1] = 1.0F;
         }

         if (var9.getProperties().Is(IsoFlagType.water) || var10.getProperties().Is(IsoFlagType.water) || var11.getProperties().Is(IsoFlagType.water)) {
            this.bShore = true;
            this.depth[2] = 1.0F;
         }

         if (var11.getProperties().Is(IsoFlagType.water) || var12.getProperties().Is(IsoFlagType.water) || var7.getProperties().Is(IsoFlagType.water)) {
            this.bShore = true;
            this.depth[3] = 1.0F;
         }
      }

    Vector2f var15 = IsoWaterFlow.getFlow(var1, 0, 0, tempVector2f);
      this.flow[0] = var15.x;
      this.speed[0] = var15.y;
      var15 = IsoWaterFlow.getFlow(var1, 0, 1, var15);
      this.flow[1] = var15.x;
      this.speed[1] = var15.y;
      var15 = IsoWaterFlow.getFlow(var1, 1, 1, var15);
      this.flow[2] = var15.x;
      this.speed[2] = var15.y;
      var15 = IsoWaterFlow.getFlow(var1, 1, 0, var15);
      this.flow[3] = var15.x;
      this.speed[3] = var15.y;
      this.hideWaterObjects(var1);
    return this;
   }

    void hideWaterObjects(IsoGridSquare var1) {
    PZArrayList var2 = var1.getObjects();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoObject var4 = (IsoObject)var2.get(var3);
         if (var4.sprite != nullptr && var4.sprite.name != nullptr) {
    std::string var5 = var4.sprite.name;
            if (var5.startsWith("blends_natural_02")
               && (
                  var5.endsWith("_0")
                     || var5.endsWith("_1")
                     || var5.endsWith("_2")
                     || var5.endsWith("_3")
                     || var5.endsWith("_4")
                     || var5.endsWith("_5")
                     || var5.endsWith("_6")
                     || var5.endsWith("_7")
                     || var5.endsWith("_8")
                     || var5.endsWith("_9")
                     || var5.endsWith("_10")
                     || var5.endsWith("_11")
                     || var5.endsWith("_12")
               )) {
               var4.sprite.setHideForWaterRender();
            }
         }
      }
   }

    bool isShore() {
      return IsoWaterFlow.getShore(this.square.x, this.square.y) == 0;
   }

    float getFlow() {
      IsoWaterFlow.getShore(this.square.x, this.square.y);
    Vector2f var1 = IsoWaterFlow.getFlow(this.square, 0, 0, tempVector2f);
      System.out.println("FLOW!  " + var1.x + " " + var1.y);
      return var1.x;
   }
}
} // namespace iso
} // namespace zombie
