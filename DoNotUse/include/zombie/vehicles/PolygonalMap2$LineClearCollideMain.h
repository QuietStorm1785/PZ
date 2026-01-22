#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/geom/Line2D.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/vehicles/PolygonalMap2/LiangBarsky.h"
#include "zombie/vehicles/PolygonalMap2/Point.h"
#include "zombie/vehicles/PolygonalMap2/PointPool.h"
#include "zombie/vehicles/PolygonalMap2/SquareUpdateTask.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include "zombie/vehicles/PolygonalMap2/VehicleRect.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    const Vector2 perp = std::make_shared<Vector2>();
   const std::vector<Point> pts = std::make_unique<std::vector<>>();
    const VehicleRect sweepAABB = std::make_shared<VehicleRect>();
    const VehicleRect vehicleAABB = std::make_shared<VehicleRect>();
    const VehiclePoly vehiclePoly = std::make_shared<VehiclePoly>();
   const Vector2[] polyVec = new Vector2[4];
   const Vector2[] vehicleVec = new Vector2[4];
    const PointPool pointPool = std::make_shared<PointPool>();
    const LiangBarsky LB = std::make_shared<LiangBarsky>();

   PolygonalMap2$LineClearCollideMain() {
      for (int var1 = 0; var1 < 4; var1++) {
         this.polyVec[var1] = std::make_unique<Vector2>();
         this.vehicleVec[var1] = std::make_unique<Vector2>();
      }
   }

    float clamp(float var1, float var2, float var3) {
      if (var1 < var2) {
         var1 = var2;
      }

      if (var1 > var3) {
         var1 = var3;
      }

    return var1;
   }

    bool canStandAtOld(PolygonalMap2 var1, float var2, float var3, float var4, BaseVehicle var5, int var6) {
    bool var7 = (var6 & 1) != 0;
    bool var8 = (var6 & 2) != 0;
    int var9 = (int)Math.floor(var2 - 0.3F);
    int var10 = (int)Math.floor(var3 - 0.3F);
    int var11 = (int)Math.ceil(var2 + 0.3F);
    int var12 = (int)Math.ceil(var3 + 0.3F);

      for (int var13 = var10; var13 < var12; var13++) {
         for (int var14 = var9; var14 < var11; var14++) {
    bool var15 = var2 >= var14 && var3 >= var13 && var2 < var14 + 1 && var3 < var13 + 1;
    IsoGridSquare var16 = IsoWorld.instance.CurrentCell.getGridSquare(var14, var13, (int)var4);
    bool var17 = false;
            if (!var15 && var16 != nullptr && var16.HasStairsNorth()) {
               var17 = var2 < var16.x || var2 >= var16.x + 1 || var16.Has(IsoObjectType.stairsTN) && var3 < var16.y;
            } else if (!var15 && var16 != nullptr && var16.HasStairsWest()) {
               var17 = var3 < var16.y || var3 >= var16.y + 1 || var16.Has(IsoObjectType.stairsTW) && var2 < var16.x;
            }

            if (var16 != nullptr
               && !var16.isSolid()
               && (!var16.isSolidTrans() || var16.isAdjacentToWindow())
               && !var17
               && (var16.SolidFloorCached ? var16.SolidFloor : var16.TreatAsSolidFloor())) {
               if (!var8) {
                  if (var16.Is(IsoFlagType.collideW) || !var7 && var16.hasBlockedDoor(false)) {
    float var28 = var14;
    float var31 = this.clamp(var3, var13, var13 + 1);
    float var34 = var2 - var28;
    float var37 = var3 - var31;
    float var40 = var34 * var34 + var37 * var37;
                     if (var40 < 0.09F) {
    return false;
                     }
                  }

                  if (var16.Is(IsoFlagType.collideN) || !var7 && var16.hasBlockedDoor(true)) {
    float var29 = this.clamp(var2, var14, var14 + 1);
    float var32 = var13;
    float var35 = var2 - var29;
    float var38 = var3 - var32;
    float var41 = var35 * var35 + var38 * var38;
                     if (var41 < 0.09F) {
    return false;
                     }
                  }
               }
            } else if (var8) {
               if (var15) {
    return false;
               }
            } else {
    float var18 = this.clamp(var2, var14, var14 + 1);
    float var19 = this.clamp(var3, var13, var13 + 1);
    float var20 = var2 - var18;
    float var21 = var3 - var19;
    float var22 = var20 * var20 + var21 * var21;
               if (var22 < 0.09F) {
    return false;
               }
            }
         }
      }

    int var23 = ((int)var2 - 4) / 10 - 1;
    int var24 = ((int)var3 - 4) / 10 - 1;
    int var25 = (int)Math.ceil((var2 + 4.0F) / 10.0F) + 1;
    int var26 = (int)Math.ceil((var3 + 4.0F) / 10.0F) + 1;

      for (int var27 = var24; var27 < var26; var27++) {
         for (int var30 = var23; var30 < var25; var30++) {
            IsoChunk var33 = GameServer.bServer
               ? ServerMap.instance.getChunk(var30, var27)
               : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var30 * 10, var27 * 10, 0);
            if (var33 != nullptr) {
               for (int var36 = 0; var36 < var33.vehicles.size(); var36++) {
    BaseVehicle var39 = (BaseVehicle)var33.vehicles.get(var36);
                  if (var39 != var5 && var39.addedToWorld && (int)var39.z == (int)var4 && var39.getPolyPlusRadius().containsPoint(var2, var3)) {
    return false;
                  }
               }
            }
         }
      }

    return true;
   }

    bool canStandAtClipper(PolygonalMap2 var1, float var2, float var3, float var4, BaseVehicle var5, int var6) {
      return PolygonalMap2.instance.collideWithObstaclesPoly.canStandAt(var2, var3, var4, var5, var6);
   }

    void drawCircle(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      LineDrawer.DrawIsoCircle(var1, var2, var3, var4, 16, var5, var6, var7, var8);
   }

    bool isNotClearOld(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, BaseVehicle var7, int var8) {
    bool var9 = (var8 & 1) != 0;
    bool var10 = (var8 & 2) != 0;
    bool var11 = (var8 & 4) != 0;
    bool var12 = (var8 & 8) != 0;
    IsoGridSquare var13 = IsoWorld.instance.CurrentCell.getGridSquare((int)var2, (int)var3, var6);
      if (var13 != nullptr && var13.HasStairs()) {
         return !var13.isSameStaircase((int)var4, (int)var5, var6);
      } else if (!this.canStandAtOld(var1, var4, var5, var6, var7, var8)) {
         if (var12) {
            this.drawCircle(var4, var5, var6, 0.3F, 1.0F, 0.0F, 0.0F, 1.0F);
         }

    return true;
      } else {
    float var14 = var5 - var3;
    float var15 = -(var4 - var2);
         this.perp.set(var14, var15);
         this.perp.normalize();
    float var16 = var2 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var17 = var3 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var18 = var4 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var19 = var5 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
         this.perp.set(-var14, -var15);
         this.perp.normalize();
    float var20 = var2 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var21 = var3 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var22 = var4 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var23 = var5 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;

         for (int var24 = 0; var24 < this.pts.size(); var24++) {
            this.pointPool.release(this.pts.get(var24));
         }

         this.pts.clear();
         this.pts.push_back(this.pointPool.alloc().init((int)var2, (int)var3));
         if ((int)var2 != (int)var4 || (int)var3 != (int)var5) {
            this.pts.push_back(this.pointPool.alloc().init((int)var4, (int)var5));
         }

         var1.supercover(var16, var17, var18, var19, var6, this.pointPool, this.pts);
         var1.supercover(var20, var21, var22, var23, var6, this.pointPool, this.pts);
         if (var12) {
            for (int var48 = 0; var48 < this.pts.size(); var48++) {
    Point var25 = this.pts.get(var48);
               LineDrawer.addLine(var25.x, var25.y, var6, var25.x + 1.0F, var25.y + 1.0F, var6, 1.0F, 1.0F, 0.0F, nullptr, false);
            }
         }

    bool var49 = false;

         for (int var50 = 0; var50 < this.pts.size(); var50++) {
    Point var26 = this.pts.get(var50);
            var13 = IsoWorld.instance.CurrentCell.getGridSquare(var26.x, var26.y, var6);
            if (var11 && var13 != nullptr && SquareUpdateTask.getCost(var13) > 0) {
    return true;
            }

            if (var13 != nullptr
               && !var13.isSolid()
               && (!var13.isSolidTrans() || var13.isAdjacentToWindow())
               && !var13.HasStairs()
               && (var13.SolidFloorCached ? var13.SolidFloor : var13.TreatAsSolidFloor())) {
               if (var13.Is(IsoFlagType.collideW) || !var9 && var13.hasBlockedDoor(false)) {
    float var53 = 0.3F;
    float var56 = 0.3F;
    float var59 = 0.3F;
    float var62 = 0.3F;
                  if (var2 < var26.x && var4 < var26.x) {
                     var53 = 0.0F;
                  } else if (var2 >= var26.x && var4 >= var26.x) {
                     var59 = 0.0F;
                  }

                  if (var3 < var26.y && var5 < var26.y) {
                     var56 = 0.0F;
                  } else if (var3 >= var26.y + 1 && var5 >= var26.y + 1) {
                     var62 = 0.0F;
                  }

                  if (this.LB
                     .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var26.x - var53, var26.y - var56, var26.x + var59, var26.y + 1.0F + var62)) {
                     if (!var12) {
    return true;
                     }

                     LineDrawer.addLine(var26.x - var53, var26.y - var56, var6, var26.x + var59, var26.y + 1.0F + var62, var6, 1.0F, 0.0F, 0.0F, nullptr, false);
                     var49 = true;
                  }
               }

               if (var13.Is(IsoFlagType.collideN) || !var9 && var13.hasBlockedDoor(true)) {
    float var54 = 0.3F;
    float var57 = 0.3F;
    float var60 = 0.3F;
    float var63 = 0.3F;
                  if (var2 < var26.x && var4 < var26.x) {
                     var54 = 0.0F;
                  } else if (var2 >= var26.x + 1 && var4 >= var26.x + 1) {
                     var60 = 0.0F;
                  }

                  if (var3 < var26.y && var5 < var26.y) {
                     var57 = 0.0F;
                  } else if (var3 >= var26.y && var5 >= var26.y) {
                     var63 = 0.0F;
                  }

                  if (this.LB
                     .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var26.x - var54, var26.y - var57, var26.x + 1.0F + var60, var26.y + var63)) {
                     if (!var12) {
    return true;
                     }

                     LineDrawer.addLine(var26.x - var54, var26.y - var57, var6, var26.x + 1.0F + var60, var26.y + var63, var6, 1.0F, 0.0F, 0.0F, nullptr, false);
                     var49 = true;
                  }
               }
            } else {
    float var27 = 0.3F;
    float var28 = 0.3F;
    float var29 = 0.3F;
    float var30 = 0.3F;
               if (var2 < var26.x && var4 < var26.x) {
                  var27 = 0.0F;
               } else if (var2 >= var26.x + 1 && var4 >= var26.x + 1) {
                  var29 = 0.0F;
               }

               if (var3 < var26.y && var5 < var26.y) {
                  var28 = 0.0F;
               } else if (var3 >= var26.y + 1 && var5 >= var26.y + 1) {
                  var30 = 0.0F;
               }

               if (this.LB
                  .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var26.x - var27, var26.y - var28, var26.x + 1.0F + var29, var26.y + 1.0F + var30)) {
                  if (!var12) {
    return true;
                  }

                  LineDrawer.addLine(
                     var26.x - var27, var26.y - var28, var6, var26.x + 1.0F + var29, var26.y + 1.0F + var30, var6, 1.0F, 0.0F, 0.0F, nullptr, false
                  );
                  var49 = true;
               }
            }
         }

    float var51 = BaseVehicle.PLUS_RADIUS;
         this.perp.set(var14, var15);
         this.perp.normalize();
         var16 = var2 + this.perp.x * var51;
         var17 = var3 + this.perp.y * var51;
         var18 = var4 + this.perp.x * var51;
         var19 = var5 + this.perp.y * var51;
         this.perp.set(-var14, -var15);
         this.perp.normalize();
         var20 = var2 + this.perp.x * var51;
         var21 = var3 + this.perp.y * var51;
         var22 = var4 + this.perp.x * var51;
         var23 = var5 + this.perp.y * var51;
    float var52 = Math.min(var16, Math.min(var18, Math.min(var20, var22)));
    float var55 = Math.min(var17, Math.min(var19, Math.min(var21, var23)));
    float var58 = Math.max(var16, Math.max(var18, Math.max(var20, var22)));
    float var61 = Math.max(var17, Math.max(var19, Math.max(var21, var23)));
         this.sweepAABB.init((int)var52, (int)var55, (int)Math.ceil(var58) - (int)var52, (int)Math.ceil(var61) - (int)var55, var6);
         this.polyVec[0].set(var16, var17);
         this.polyVec[1].set(var18, var19);
         this.polyVec[2].set(var22, var23);
         this.polyVec[3].set(var20, var21);
    int var64 = this.sweepAABB.left() / 10 - 1;
    int var31 = this.sweepAABB.top() / 10 - 1;
    int var32 = (int)Math.ceil(this.sweepAABB.right() / 10.0F) + 1;
    int var33 = (int)Math.ceil(this.sweepAABB.bottom() / 10.0F) + 1;

         for (int var34 = var31; var34 < var33; var34++) {
            for (int var35 = var64; var35 < var32; var35++) {
               IsoChunk var36 = GameServer.bServer
                  ? ServerMap.instance.getChunk(var35, var34)
                  : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var35 * 10, var34 * 10, 0);
               if (var36 != nullptr) {
                  for (int var37 = 0; var37 < var36.vehicles.size(); var37++) {
    BaseVehicle var38 = (BaseVehicle)var36.vehicles.get(var37);
                     if (var38 != var7 && var38.VehicleID != -1) {
                        this.vehiclePoly.init(var38.getPoly());
                        this.vehiclePoly.getAABB(this.vehicleAABB);
                        if (this.vehicleAABB.intersects(this.sweepAABB) && this.polyVehicleIntersect(this.vehiclePoly, var12)) {
                           var49 = true;
                           if (!var12) {
    return true;
                           }
                        }
                     }
                  }
               }
            }
         }

    return var49;
      }
   }

    bool isNotClearClipper(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, BaseVehicle var7, int var8) {
    bool var9 = (var8 & 1) != 0;
    bool var10 = (var8 & 2) != 0;
    bool var11 = (var8 & 4) != 0;
    bool var12 = (var8 & 8) != 0;
    IsoGridSquare var13 = IsoWorld.instance.CurrentCell.getGridSquare((int)var2, (int)var3, var6);
      if (var13 != nullptr && var13.HasStairs()) {
         return !var13.isSameStaircase((int)var4, (int)var5, var6);
      } else if (!this.canStandAtClipper(var1, var4, var5, var6, var7, var8)) {
         if (var12) {
            this.drawCircle(var4, var5, var6, 0.3F, 1.0F, 0.0F, 0.0F, 1.0F);
         }

    return true;
      } else {
         return PolygonalMap2.instance.collideWithObstaclesPoly.isNotClear(var2, var3, var4, var5, var6, var12, var7, var9, var10);
      }
   }

    bool isNotClear(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, BaseVehicle var7, int var8) {
      return this.isNotClearOld(var1, var2, var3, var4, var5, var6, var7, var8);
   }

    Vector2 getCollidepoint(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, BaseVehicle var7, int var8) {
    bool var9 = (var8 & 1) != 0;
    bool var10 = (var8 & 2) != 0;
    bool var11 = (var8 & 4) != 0;
    bool var12 = (var8 & 8) != 0;
    float var14 = var5 - var3;
    float var15 = -(var4 - var2);
      this.perp.set(var14, var15);
      this.perp.normalize();
    float var16 = var2 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var17 = var3 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var18 = var4 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var19 = var5 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
      this.perp.set(-var14, -var15);
      this.perp.normalize();
    float var20 = var2 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var21 = var3 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var22 = var4 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var23 = var5 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;

      for (int var24 = 0; var24 < this.pts.size(); var24++) {
         this.pointPool.release(this.pts.get(var24));
      }

      this.pts.clear();
      this.pts.push_back(this.pointPool.alloc().init((int)var2, (int)var3));
      if ((int)var2 != (int)var4 || (int)var3 != (int)var5) {
         this.pts.push_back(this.pointPool.alloc().init((int)var4, (int)var5));
      }

      var1.supercover(var16, var17, var18, var19, var6, this.pointPool, this.pts);
      var1.supercover(var20, var21, var22, var23, var6, this.pointPool, this.pts);
      this.pts
         .sort((var2x, var3x) -> (int)(IsoUtils.DistanceManhatten(var2, var3, var2x.x, var2x.y) - IsoUtils.DistanceManhatten(var2, var3, var3x.x, var3x.y)));
      if (var12) {
         for (int var30 = 0; var30 < this.pts.size(); var30++) {
    Point var25 = this.pts.get(var30);
            LineDrawer.addLine(var25.x, var25.y, var6, var25.x + 1.0F, var25.y + 1.0F, var6, 1.0F, 1.0F, 0.0F, nullptr, false);
         }
      }

      for (int var31 = 0; var31 < this.pts.size(); var31++) {
    Point var32 = this.pts.get(var31);
    IsoGridSquare var13 = IsoWorld.instance.CurrentCell.getGridSquare(var32.x, var32.y, var6);
         if (var11 && var13 != nullptr && SquareUpdateTask.getCost(var13) > 0) {
            return PolygonalMap2.temp.set(var32.x + 0.5F, var32.y + 0.5F);
         }

         if (var13 != nullptr
            && !var13.isSolid()
            && (!var13.isSolidTrans() || var13.isAdjacentToWindow())
            && !var13.HasStairs()
            && (var13.SolidFloorCached ? var13.SolidFloor : var13.TreatAsSolidFloor())) {
            if (var13.Is(IsoFlagType.collideW) || !var9 && var13.hasBlockedDoor(false)) {
    float var33 = 0.3F;
    float var35 = 0.3F;
    float var37 = 0.3F;
    float var39 = 0.3F;
               if (var2 < var32.x && var4 < var32.x) {
                  var33 = 0.0F;
               } else if (var2 >= var32.x && var4 >= var32.x) {
                  var37 = 0.0F;
               }

               if (var3 < var32.y && var5 < var32.y) {
                  var35 = 0.0F;
               } else if (var3 >= var32.y + 1 && var5 >= var32.y + 1) {
                  var39 = 0.0F;
               }

               if (this.LB.lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var32.x - var33, var32.y - var35, var32.x + var37, var32.y + 1.0F + var39)) {
                  if (var12) {
                     LineDrawer.addLine(var32.x - var33, var32.y - var35, var6, var32.x + var37, var32.y + 1.0F + var39, var6, 1.0F, 0.0F, 0.0F, nullptr, false);
                  }

                  return PolygonalMap2.temp.set(var32.x + (var2 - var4 < 0.0F ? -0.5F : 0.5F), var32.y + 0.5F);
               }
            }

            if (var13.Is(IsoFlagType.collideN) || !var9 && var13.hasBlockedDoor(true)) {
    float var34 = 0.3F;
    float var36 = 0.3F;
    float var38 = 0.3F;
    float var40 = 0.3F;
               if (var2 < var32.x && var4 < var32.x) {
                  var34 = 0.0F;
               } else if (var2 >= var32.x + 1 && var4 >= var32.x + 1) {
                  var38 = 0.0F;
               }

               if (var3 < var32.y && var5 < var32.y) {
                  var36 = 0.0F;
               } else if (var3 >= var32.y && var5 >= var32.y) {
                  var40 = 0.0F;
               }

               if (this.LB.lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var32.x - var34, var32.y - var36, var32.x + 1.0F + var38, var32.y + var40)) {
                  if (var12) {
                     LineDrawer.addLine(var32.x - var34, var32.y - var36, var6, var32.x + 1.0F + var38, var32.y + var40, var6, 1.0F, 0.0F, 0.0F, nullptr, false);
                  }

                  return PolygonalMap2.temp.set(var32.x + 0.5F, var32.y + (var3 - var5 < 0.0F ? -0.5F : 0.5F));
               }
            }
         } else {
    float var26 = 0.3F;
    float var27 = 0.3F;
    float var28 = 0.3F;
    float var29 = 0.3F;
            if (var2 < var32.x && var4 < var32.x) {
               var26 = 0.0F;
            } else if (var2 >= var32.x + 1 && var4 >= var32.x + 1) {
               var28 = 0.0F;
            }

            if (var3 < var32.y && var5 < var32.y) {
               var27 = 0.0F;
            } else if (var3 >= var32.y + 1 && var5 >= var32.y + 1) {
               var29 = 0.0F;
            }

            if (this.LB
               .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var32.x - var26, var32.y - var27, var32.x + 1.0F + var28, var32.y + 1.0F + var29)) {
               if (var12) {
                  LineDrawer.addLine(
                     var32.x - var26, var32.y - var27, var6, var32.x + 1.0F + var28, var32.y + 1.0F + var29, var6, 1.0F, 0.0F, 0.0F, nullptr, false
                  );
               }

               return PolygonalMap2.temp.set(var32.x + 0.5F, var32.y + 0.5F);
            }
         }
      }

      return PolygonalMap2.temp.set(var4, var5);
   }

    bool polyVehicleIntersect(VehiclePoly var1, bool var2) {
      this.vehicleVec[0].set(var1.x1, var1.y1);
      this.vehicleVec[1].set(var1.x2, var1.y2);
      this.vehicleVec[2].set(var1.x3, var1.y3);
      this.vehicleVec[3].set(var1.x4, var1.y4);
    bool var3 = false;

      for (int var4 = 0; var4 < 4; var4++) {
    Vector2 var5 = this.polyVec[var4];
    Vector2 var6 = var4 == 3 ? this.polyVec[0] : this.polyVec[var4 + 1];

         for (int var7 = 0; var7 < 4; var7++) {
    Vector2 var8 = this.vehicleVec[var7];
    Vector2 var9 = var7 == 3 ? this.vehicleVec[0] : this.vehicleVec[var7 + 1];
            if (Line2D.linesIntersect(var5.x, var5.y, var6.x, var6.y, var8.x, var8.y, var9.x, var9.y)) {
               if (var2) {
                  LineDrawer.addLine(var5.x, var5.y, 0.0F, var6.x, var6.y, 0.0F, 1.0F, 0.0F, 0.0F, nullptr, true);
                  LineDrawer.addLine(var8.x, var8.y, 0.0F, var9.x, var9.y, 0.0F, 1.0F, 0.0F, 0.0F, nullptr, true);
               }

               var3 = true;
            }
         }
      }

    return var3;
   }
}
} // namespace vehicles
} // namespace zombie
