#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include "zombie/vehicles/PolygonalMap2/ChunkDataZ.h"
#include "zombie/vehicles/PolygonalMap2/LiangBarsky.h"
#include "zombie/vehicles/PolygonalMap2/Obstacle.h"
#include "zombie/vehicles/PolygonalMap2/Point.h"
#include "zombie/vehicles/PolygonalMap2/PointPool.h"
#include "zombie/vehicles/PolygonalMap2/Square.h"
#include "zombie/vehicles/PolygonalMap2/Vehicle.h"
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
   const Vector2[] polyVec = new Vector2[4];
   const Vector2[] vehicleVec = new Vector2[4];
    const PointPool pointPool = std::make_shared<PointPool>();
    const LiangBarsky LB = std::make_shared<LiangBarsky>();

   PolygonalMap2$LineClearCollide() {
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

    bool canStandAt(PolygonalMap2 var1, float var2, float var3, float var4, float var5, float var6, Vehicle var7) {
      if (((int)var2 != (int)var4 || (int)var3 != (int)var5) && var1.isBlockedInAllDirections((int)var4, (int)var5, (int)var6)) {
    return false;
      } else {
    int var8 = (int)Math.floor(var4 - 0.3F);
    int var9 = (int)Math.floor(var5 - 0.3F);
    int var10 = (int)Math.ceil(var4 + 0.3F);
    int var11 = (int)Math.ceil(var5 + 0.3F);

         for (int var12 = var9; var12 < var11; var12++) {
            for (int var13 = var8; var13 < var10; var13++) {
    Square var14 = var1.getSquare(var13, var12, (int)var6);
    bool var15 = var4 >= var13 && var5 >= var12 && var4 < var13 + 1 && var5 < var12 + 1;
    bool var16 = false;
               if (!var15 && var14 != nullptr && var14.has(448)) {
                  var16 = var4 < var14.x || var4 >= var14.x + 1 || var14.has(64) && var5 < var14.y;
               } else if (!var15 && var14 != nullptr && var14.has(56)) {
                  var16 = var5 < var14.y || var5 >= var14.y + 1 || var14.has(8) && var4 < var14.x;
               }

               if ((var14 == nullptr || var14.isReallySolid() || var16 || !var14.has(512)) && var15) {
    return false;
               }
            }
         }

         for (int var17 = 0; var17 < var1.vehicles.size(); var17++) {
    Vehicle var18 = (Vehicle)var1.vehicles.get(var17);
            if (var18 != var7 && (int)var18.polyPlusRadius.z == (int)var6 && var18.polyPlusRadius.containsPoint(var4, var5)) {
    return false;
            }
         }

    return true;
      }
   }

    bool canStandAtClipper(PolygonalMap2 var1, float var2, float var3, float var4, float var5, float var6, Vehicle var7, int var8) {
      if (((int)var2 != (int)var4 || (int)var3 != (int)var5) && var1.isBlockedInAllDirections((int)var4, (int)var5, (int)var6)) {
    return false;
      } else {
    Chunk var9 = var1.getChunkFromSquarePos((int)var4, (int)var5);
         if (var9 == nullptr) {
    return false;
         } else {
    ChunkDataZ var10 = var9.collision.init(var9, (int)var6);

            for (int var11 = 0; var11 < var10.obstacles.size(); var11++) {
    Obstacle var12 = (Obstacle)var10.obstacles.get(var11);
               if ((var7 == nullptr || var12.vehicle != var7) && var12.bounds.containsPoint(var4, var5) && var12.isPointInside(var4, var5, var8)) {
    return false;
               }
            }

    return true;
         }
      }
   }

    float isLeft(float var1, float var2, float var3, float var4, float var5, float var6) {
      return (var3 - var1) * (var6 - var2) - (var5 - var1) * (var4 - var2);
   }

    bool isPointInPolygon_WindingNumber(float var1, float var2, VehiclePoly var3) {
      this.polyVec[0].set(var3.x1, var3.y1);
      this.polyVec[1].set(var3.x2, var3.y2);
      this.polyVec[2].set(var3.x3, var3.y3);
      this.polyVec[3].set(var3.x4, var3.y4);
    int var4 = 0;

      for (int var5 = 0; var5 < 4; var5++) {
    Vector2 var6 = this.polyVec[var5];
    Vector2 var7 = var5 == 3 ? this.polyVec[0] : this.polyVec[var5 + 1];
         if (var6.y <= var2) {
            if (var7.y > var2 && this.isLeft(var6.x, var6.y, var7.x, var7.y, var1, var2) > 0.0F) {
               var4++;
            }
         } else if (var7.y <= var2 && this.isLeft(var6.x, var6.y, var7.x, var7.y, var1, var2) < 0.0F) {
            var4--;
         }
      }

      return var4 != 0;
   }

    bool isNotClearOld(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, int var7) {
    bool var8 = (var7 & 4) != 0;
    Square var9 = var1.getSquare((int)var2, (int)var3, var6);
      if (var9 != nullptr && var9.has(504)) {
    return true;
      } else if (!this.canStandAt(var1, var2, var3, var4, var5, var6, nullptr)) {
    return true;
      } else {
    float var10 = var5 - var3;
    float var11 = -(var4 - var2);
         this.perp.set(var10, var11);
         this.perp.normalize();
    float var12 = var2 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var13 = var3 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var14 = var4 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var15 = var5 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
         this.perp.set(-var10, -var11);
         this.perp.normalize();
    float var16 = var2 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var17 = var3 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var18 = var4 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var19 = var5 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;

         for (int var20 = 0; var20 < this.pts.size(); var20++) {
            this.pointPool.release(this.pts.get(var20));
         }

         this.pts.clear();
         this.pts.push_back(this.pointPool.alloc().init((int)var2, (int)var3));
         if ((int)var2 != (int)var4 || (int)var3 != (int)var5) {
            this.pts.push_back(this.pointPool.alloc().init((int)var4, (int)var5));
         }

         var1.supercover(var12, var13, var14, var15, var6, this.pointPool, this.pts);
         var1.supercover(var16, var17, var18, var19, var6, this.pointPool, this.pts);

         for (int var37 = 0; var37 < this.pts.size(); var37++) {
    Point var21 = this.pts.get(var37);
            var9 = var1.getSquare(var21.x, var21.y, var6);
            if (var8 && var9 != nullptr && var9.cost > 0) {
    return true;
            }

            if (var9 != nullptr && !var9.isReallySolid() && !var9.has(504) && var9.has(512)) {
               if (var9.isCollideW()) {
    float var40 = 0.3F;
    float var43 = 0.3F;
    float var46 = 0.3F;
    float var49 = 0.3F;
                  if (var2 < var21.x && var4 < var21.x) {
                     var40 = 0.0F;
                  } else if (var2 >= var21.x && var4 >= var21.x) {
                     var46 = 0.0F;
                  }

                  if (var3 < var21.y && var5 < var21.y) {
                     var43 = 0.0F;
                  } else if (var3 >= var21.y + 1 && var5 >= var21.y + 1) {
                     var49 = 0.0F;
                  }

                  if (this.LB
                     .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var21.x - var40, var21.y - var43, var21.x + var46, var21.y + 1.0F + var49)) {
    return true;
                  }
               }

               if (var9.isCollideN()) {
    float var41 = 0.3F;
    float var44 = 0.3F;
    float var47 = 0.3F;
    float var50 = 0.3F;
                  if (var2 < var21.x && var4 < var21.x) {
                     var41 = 0.0F;
                  } else if (var2 >= var21.x + 1 && var4 >= var21.x + 1) {
                     var47 = 0.0F;
                  }

                  if (var3 < var21.y && var5 < var21.y) {
                     var44 = 0.0F;
                  } else if (var3 >= var21.y && var5 >= var21.y) {
                     var50 = 0.0F;
                  }

                  if (this.LB
                     .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var21.x - var41, var21.y - var44, var21.x + 1.0F + var47, var21.y + var50)) {
    return true;
                  }
               }
            } else {
    float var22 = 0.3F;
    float var23 = 0.3F;
    float var24 = 0.3F;
    float var25 = 0.3F;
               if (var2 < var21.x && var4 < var21.x) {
                  var22 = 0.0F;
               } else if (var2 >= var21.x + 1 && var4 >= var21.x + 1) {
                  var24 = 0.0F;
               }

               if (var3 < var21.y && var5 < var21.y) {
                  var23 = 0.0F;
               } else if (var3 >= var21.y + 1 && var5 >= var21.y + 1) {
                  var25 = 0.0F;
               }

               if (this.LB
                  .lineRectIntersect(var2, var3, var4 - var2, var5 - var3, var21.x - var22, var21.y - var23, var21.x + 1.0F + var24, var21.y + 1.0F + var25)) {
    return true;
               }
            }
         }

    float var38 = BaseVehicle.PLUS_RADIUS;
         this.perp.set(var10, var11);
         this.perp.normalize();
         var12 = var2 + this.perp.x * var38;
         var13 = var3 + this.perp.y * var38;
         var14 = var4 + this.perp.x * var38;
         var15 = var5 + this.perp.y * var38;
         this.perp.set(-var10, -var11);
         this.perp.normalize();
         var16 = var2 + this.perp.x * var38;
         var17 = var3 + this.perp.y * var38;
         var18 = var4 + this.perp.x * var38;
         var19 = var5 + this.perp.y * var38;
    float var39 = Math.min(var12, Math.min(var14, Math.min(var16, var18)));
    float var42 = Math.min(var13, Math.min(var15, Math.min(var17, var19)));
    float var45 = Math.max(var12, Math.max(var14, Math.max(var16, var18)));
    float var48 = Math.max(var13, Math.max(var15, Math.max(var17, var19)));
         this.sweepAABB.init((int)var39, (int)var42, (int)Math.ceil(var45) - (int)var39, (int)Math.ceil(var48) - (int)var42, var6);
         this.polyVec[0].set(var12, var13);
         this.polyVec[1].set(var14, var15);
         this.polyVec[2].set(var18, var19);
         this.polyVec[3].set(var16, var17);

         for (int var51 = 0; var51 < var1.vehicles.size(); var51++) {
    Vehicle var26 = (Vehicle)var1.vehicles.get(var51);
    VehicleRect var27 = var26.poly.getAABB(this.vehicleAABB);
            if (var27.intersects(this.sweepAABB) && this.polyVehicleIntersect(var26.poly)) {
    return true;
            }
         }

    return false;
      }
   }

    bool isNotClearClipper(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, int var7) {
    bool var8 = (var7 & 4) != 0;
    Square var9 = var1.getSquare((int)var2, (int)var3, var6);
      if (var9 != nullptr && var9.has(504)) {
    return true;
      } else if (!this.canStandAtClipper(var1, var2, var3, var4, var5, var6, nullptr, var7)) {
    return true;
      } else {
    float var10 = var2 / 10.0F;
    float var11 = var3 / 10.0F;
    float var12 = var4 / 10.0F;
    float var13 = var5 / 10.0F;
    double var14 = Math.abs(var12 - var10);
    double var16 = Math.abs(var13 - var11);
    int var18 = (int)Math.floor(var10);
    int var19 = (int)Math.floor(var11);
    int var20 = 1;
    uint8_t var21;
    double var23;
         if (var14 == 0.0) {
            var21 = 0;
            var23 = double.POSITIVE_INFINITY;
         } else if (var12 > var10) {
            var21 = 1;
            var20 += (int)Math.floor(var12) - var18;
            var23 = (Math.floor(var10) + 1.0 - var10) * var16;
         } else {
            var21 = -1;
            var20 += var18 - (int)Math.floor(var12);
            var23 = (var10 - Math.floor(var10)) * var16;
         }

    uint8_t var22;
         if (var16 == 0.0) {
            var22 = 0;
            var23 -= double.POSITIVE_INFINITY;
         } else if (var13 > var11) {
            var22 = 1;
            var20 += (int)Math.floor(var13) - var19;
            var23 -= (Math.floor(var11) + 1.0 - var11) * var14;
         } else {
            var22 = -1;
            var20 += var19 - (int)Math.floor(var13);
            var23 -= (var11 - Math.floor(var11)) * var14;
         }

         for (; var20 > 0; var20--) {
    Chunk var25 = PolygonalMap2.instance.getChunkFromChunkPos(var18, var19);
            if (var25 != nullptr) {
    ChunkDataZ var26 = var25.collision.init(var25, var6);
    std::vector var27 = var26.obstacles;

               for (int var28 = 0; var28 < var27.size(); var28++) {
    Obstacle var29 = (Obstacle)var27.get(var28);
                  if (var29.lineSegmentIntersects(var2, var3, var4, var5)) {
    return true;
                  }
               }
            }

            if (var23 > 0.0) {
               var19 += var22;
               var23 -= var14;
            } else {
               var18 += var21;
               var23 += var16;
            }
         }

         return var8 && this.isNotClearCost(var2, var3, var4, var5, var6);
      }
   }

    bool isNotClearCost(float var1, float var2, float var3, float var4, int var5) {
    float var6 = var4 - var2;
    float var7 = -(var3 - var1);
      this.perp.set(var6, var7);
      this.perp.normalize();
    float var8 = var1 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var9 = var2 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var10 = var3 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var11 = var4 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
      this.perp.set(-var6, -var7);
      this.perp.normalize();
    float var12 = var1 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var13 = var2 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;
    float var14 = var3 + this.perp.x * PolygonalMap2.RADIUS_DIAGONAL;
    float var15 = var4 + this.perp.y * PolygonalMap2.RADIUS_DIAGONAL;

      for (int var16 = 0; var16 < this.pts.size(); var16++) {
         this.pointPool.release(this.pts.get(var16));
      }

      this.pts.clear();
      this.pts.push_back(this.pointPool.alloc().init((int)var1, (int)var2));
      if ((int)var1 != (int)var3 || (int)var2 != (int)var4) {
         this.pts.push_back(this.pointPool.alloc().init((int)var3, (int)var4));
      }

      PolygonalMap2.instance.supercover(var8, var9, var10, var11, var5, this.pointPool, this.pts);
      PolygonalMap2.instance.supercover(var12, var13, var14, var15, var5, this.pointPool, this.pts);

      for (int var19 = 0; var19 < this.pts.size(); var19++) {
    Point var17 = this.pts.get(var19);
    Square var18 = PolygonalMap2.instance.getSquare(var17.x, var17.y, var5);
         if (var18 != nullptr && var18.cost > 0) {
    return true;
         }
      }

    return false;
   }

    bool isNotClear(PolygonalMap2 var1, float var2, float var3, float var4, float var5, int var6, int var7) {
      return this.isNotClearOld(var1, var2, var3, var4, var5, var6, var7);
   }

    bool polyVehicleIntersect(VehiclePoly var1) {
      this.vehicleVec[0].set(var1.x1, var1.y1);
      this.vehicleVec[1].set(var1.x2, var1.y2);
      this.vehicleVec[2].set(var1.x3, var1.y3);
      this.vehicleVec[3].set(var1.x4, var1.y4);
    bool var2 = false;

      for (int var3 = 0; var3 < 4; var3++) {
    Vector2 var4 = this.polyVec[var3];
    Vector2 var5 = var3 == 3 ? this.polyVec[0] : this.polyVec[var3 + 1];

         for (int var6 = 0; var6 < 4; var6++) {
    Vector2 var7 = this.vehicleVec[var6];
    Vector2 var8 = var6 == 3 ? this.vehicleVec[0] : this.vehicleVec[var6 + 1];
            if (Line2D.linesIntersect(var4.x, var4.y, var5.x, var5.y, var7.x, var7.y, var8.x, var8.y)) {
               var2 = true;
            }
         }
      }

    return var2;
   }
}
} // namespace vehicles
} // namespace zombie
