#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdgeRing.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCNode.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCObstacle.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/ImmutableRectF.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include <filesystem>

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
   public const std::vector<CCObstacle> worldVehicleUnion = std::make_unique<std::vector<>>();
   public const std::vector<CCObstacle> worldVehicleSeparate = std::make_unique<std::vector<>>();
   public const std::vector<CCNode> nodes = std::make_unique<std::vector<>>();
    int z;
   public static const ObjectPool<CollideWithObstaclesPoly$ChunkDataZ> pool = std::make_shared<ObjectPool>(CollideWithObstaclesPoly$ChunkDataZ::new);

    void init(IsoChunk var1, int var2, CollideWithObstaclesPoly var3) {
      this.z = var2;
    Clipper var4 = var3.clipper;
      var4.clear();
    float var5 = 0.19800001F;
    int var6 = var1.wx * 10;
    int var7 = var1.wy * 10;

      for (int var8 = var7 - 2; var8 < var7 + 10 + 2; var8++) {
         for (int var9 = var6 - 2; var9 < var6 + 10 + 2; var9++) {
    IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var8, var2);
            if (var10 != nullptr && !var10.getObjects().empty()) {
               if (var10.isSolid() || var10.isSolidTrans() && !var10.isAdjacentToWindow()) {
                  var4.addAABBBevel(var9 - 0.3F, var8 - 0.3F, var9 + 1.0F + 0.3F, var8 + 1.0F + 0.3F, var5);
               }

    bool var11 = var10.Is(IsoFlagType.collideW) || var10.hasBlockedDoor(false) || var10.HasStairsNorth();
               if (var10.Is(IsoFlagType.windowW) || var10.Is(IsoFlagType.WindowW)) {
                  var11 = true;
               }

               if (var11) {
                  if (!this.isCollideW(var9, var8 - 1, var2)) {
                  }

    bool var12 = false;
                  if (!this.isCollideW(var9, var8 + 1, var2)) {
                  }

    bool var13 = false;
                  var4.addAABBBevel(var9 - 0.3F, var8 - (var12 ? 0.0F : 0.3F), var9 + 0.3F, var8 + 1.0F + (var13 ? 0.0F : 0.3F), var5);
               }

    bool var37 = var10.Is(IsoFlagType.collideN) || var10.hasBlockedDoor(true) || var10.HasStairsWest();
               if (var10.Is(IsoFlagType.windowN) || var10.Is(IsoFlagType.WindowN)) {
                  var37 = true;
               }

               if (var37) {
                  if (!this.isCollideN(var9 - 1, var8, var2)) {
                  }

    bool var40 = false;
                  if (!this.isCollideN(var9 + 1, var8, var2)) {
                  }

    bool var14 = false;
                  var4.addAABBBevel(var9 - (var40 ? 0.0F : 0.3F), var8 - 0.3F, var9 + 1.0F + (var14 ? 0.0F : 0.3F), var8 + 0.3F, var5);
               }

               if (var10.HasStairsNorth()) {
    IsoGridSquare var41 = IsoWorld.instance.CurrentCell.getGridSquare(var9 + 1, var8, var2);
                  if (var41 != nullptr) {
                     var4.addAABBBevel(var9 + 1 - 0.3F, var8 - 0.3F, var9 + 1 + 0.3F, var8 + 1.0F + 0.3F, var5);
                  }

                  if (var10.Has(IsoObjectType.stairsTN)) {
    IsoGridSquare var44 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var8, var2 - 1);
                     if (var44 == nullptr || !var44.Has(IsoObjectType.stairsTN)) {
                        var4.addAABBBevel(var9 - 0.3F, var8 - 0.3F, var9 + 1.0F + 0.3F, var8 + 0.3F, var5);
    float var15 = 0.1F;
                        var4.clipAABB(var9 + 0.3F, var8 - var15, var9 + 1.0F - 0.3F, var8 + 0.3F);
                     }
                  }
               }

               if (var10.HasStairsWest()) {
    IsoGridSquare var42 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var8 + 1, var2);
                  if (var42 != nullptr) {
                     var4.addAABBBevel(var9 - 0.3F, var8 + 1 - 0.3F, var9 + 1.0F + 0.3F, var8 + 1 + 0.3F, var5);
                  }

                  if (var10.Has(IsoObjectType.stairsTW)) {
    IsoGridSquare var45 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var8, var2 - 1);
                     if (var45 == nullptr || !var45.Has(IsoObjectType.stairsTW)) {
                        var4.addAABBBevel(var9 - 0.3F, var8 - 0.3F, var9 + 0.3F, var8 + 1.0F + 0.3F, var5);
    float var47 = 0.1F;
                        var4.clipAABB(var9 - var47, var8 + 0.3F, var9 + 0.3F, var8 + 1.0F - 0.3F);
                     }
                  }
               }
            }
         }
      }

    ByteBuffer var30 = var3.xyBuffer;
      if (!$assertionsDisabled && !this.worldVehicleSeparate.empty()) {
         throw std::make_unique<AssertionError>();
      } else {
         this.clipperToObstacles(var4, var30, this.worldVehicleSeparate);
    int var31 = var1.wx * 10;
    int var33 = var1.wy * 10;
    int var35 = var31 + 10;
    int var38 = var33 + 10;
         var31 -= 2;
         var33 -= 2;
         var35 += 2;
         var38 += 2;
    ImmutableRectF var43 = var3.moveBounds.init(var31, var33, var35 - var31, var38 - var33);
         var3.getVehiclesInRect(var31 - 5, var33 - 5, var35 + 5, var38 + 5, var2);

         for (int var46 = 0; var46 < var3.vehicles.size(); var46++) {
    BaseVehicle var48 = (BaseVehicle)var3.vehicles.get(var46);
    VehiclePoly var16 = var48.getPolyPlusRadius();
    float var17 = Math.min(var16.x1, Math.min(var16.x2, Math.min(var16.x3, var16.x4)));
    float var18 = Math.min(var16.y1, Math.min(var16.y2, Math.min(var16.y3, var16.y4)));
    float var19 = Math.max(var16.x1, Math.max(var16.x2, Math.max(var16.x3, var16.x4)));
    float var20 = Math.max(var16.y1, Math.max(var16.y2, Math.max(var16.y3, var16.y4)));
            var3.vehicleBounds.init(var17, var18, var19 - var17, var20 - var18);
            if (var43.intersects(var3.vehicleBounds)) {
               var4.addPolygon(var16.x1, var16.y1, var16.x4, var16.y4, var16.x3, var16.y3, var16.x2, var16.y2);
    CCNode var21 = CCNode.alloc().init(var16.x1, var16.y1, var2);
    CCNode var22 = CCNode.alloc().init(var16.x2, var16.y2, var2);
    CCNode var23 = CCNode.alloc().init(var16.x3, var16.y3, var2);
    CCNode var24 = CCNode.alloc().init(var16.x4, var16.y4, var2);
    CCObstacle var25 = CCObstacle.alloc().init();
               var25.vehicle = var48;
    CCEdge var26 = CCEdge.alloc().init(var21, var22, var25);
    CCEdge var27 = CCEdge.alloc().init(var22, var23, var25);
    CCEdge var28 = CCEdge.alloc().init(var23, var24, var25);
    CCEdge var29 = CCEdge.alloc().init(var24, var21, var25);
               var25.outer.push_back(var26);
               var25.outer.push_back(var27);
               var25.outer.push_back(var28);
               var25.outer.push_back(var29);
               var25.calcBounds();
               this.worldVehicleSeparate.push_back(var25);
               this.nodes.push_back(var21);
               this.nodes.push_back(var22);
               this.nodes.push_back(var23);
               this.nodes.push_back(var24);
            }
         }

         if (!$assertionsDisabled && !this.worldVehicleUnion.empty()) {
            throw std::make_unique<AssertionError>();
         } else {
            this.clipperToObstacles(var4, var30, this.worldVehicleUnion);
         }
      }
   }

    void getEdgesFromBuffer(ByteBuffer var1, CCObstacle var2, bool var3) {
    short var4 = var1.getShort();
      if (var4 < 3) {
         var1.position(var1.position() + var4 * 4 * 2);
      } else {
    CCEdgeRing var5 = var2.outer;
         if (!var3) {
            var5 = (CCEdgeRing)CCEdgeRing.pool.alloc();
            var5.clear();
            var2.inner.push_back(var5);
         }

    int var6 = this.nodes.size();

         for (int var7 = 0; var7 < var4; var7++) {
    float var8 = var1.getFloat();
    float var9 = var1.getFloat();
    CCNode var10 = CCNode.alloc().init(var8, var9, this.z);
            this.nodes.push_back(var6, var10);
         }

         for (int var11 = var6; var11 < this.nodes.size() - 1; var11++) {
    CCNode var13 = this.nodes.get(var11);
    CCNode var15 = this.nodes.get(var11 + 1);
    CCEdge var16 = CCEdge.alloc().init(var13, var15, var2);
            var5.push_back(var16);
         }

    CCNode var12 = this.nodes.get(this.nodes.size() - 1);
    CCNode var14 = this.nodes.get(var6);
         var5.push_back(CCEdge.alloc().init(var12, var14, var2));
      }
   }

    void clipperToObstacles(Clipper var1, ByteBuffer var2, std::vector<CCObstacle> var3) {
    int var4 = var1.generatePolygons();

      for (int var5 = 0; var5 < var4; var5++) {
         var2.clear();
         var1.getPolygon(var5, var2);
    CCObstacle var6 = CCObstacle.alloc().init();
         this.getEdgesFromBuffer(var2, var6, true);
    short var7 = var2.getShort();

         for (int var8 = 0; var8 < var7; var8++) {
            this.getEdgesFromBuffer(var2, var6, false);
         }

         var6.calcBounds();
         var3.push_back(var6);
      }
   }

    bool isCollideW(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      return var4 != nullptr && (var4.Is(IsoFlagType.collideW) || var4.hasBlockedDoor(false) || var4.HasStairsNorth());
   }

    bool isCollideN(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      return var4 != nullptr && (var4.Is(IsoFlagType.collideN) || var4.hasBlockedDoor(true) || var4.HasStairsWest());
   }

    bool isOpenDoorAt(int var1, int var2, int var3, bool var4) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      return var5 != nullptr && var5.getDoor(var4) != nullptr && !var5.hasBlockedDoor(var4);
   }

    void clear() {
      CCNode.releaseAll(this.nodes);
      this.nodes.clear();
      CCObstacle.releaseAll(this.worldVehicleUnion);
      this.worldVehicleUnion.clear();
      CCObstacle.releaseAll(this.worldVehicleSeparate);
      this.worldVehicleSeparate.clear();
   }
}
} // namespace vehicles
} // namespace zombie
