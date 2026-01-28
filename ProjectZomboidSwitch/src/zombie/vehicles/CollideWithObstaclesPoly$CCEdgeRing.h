#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec3.hpp>
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdgeRing/1.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCNode.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/ClosestPointOnEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/EdgeRingHit.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
   static const ObjectPool<CollideWithObstaclesPoly$CCEdgeRing> pool = std::make_shared<1>(CollideWithObstaclesPoly$CCEdgeRing::new);

   private CollideWithObstaclesPoly$CCEdgeRing() {
   }

    float isLeft(float var1, float var2, float var3, float var4, float var5, float var6) {
      return (var3 - var1) * (var6 - var2) - (var5 - var1) * (var4 - var2);
   }

    EdgeRingHit isPointInPolygon_WindingNumber(float var1, float var2, int var3) {
    int var4 = 0;

      for (int var5 = 0; var5 < this.size(); var5++) {
    CCEdge var6 = this.get(var5);
         if ((var3 & 16) != 0 && var6.isPointOn(var1, var2)) {
            return EdgeRingHit.OnEdge;
         }

         if (var6.node1.y <= var2) {
            if (var6.node2.y > var2 && this.isLeft(var6.node1.x, var6.node1.y, var6.node2.x, var6.node2.y, var1, var2) > 0.0F) {
               var4++;
            }
         } else if (var6.node2.y <= var2 && this.isLeft(var6.node1.x, var6.node1.y, var6.node2.x, var6.node2.y, var1, var2) < 0.0F) {
            var4--;
         }
      }

    return var4 = = 0 ? EdgeRingHit.Outside : EdgeRingHit.Inside;
   }

    bool lineSegmentIntersects(float var1, float var2, float var3, float var4, bool var5, bool var6) {
      CollideWithObstaclesPoly.move.set(var3 - var1, var4 - var2);
    float var7 = CollideWithObstaclesPoly.move.getLength();
      CollideWithObstaclesPoly.move.normalize();
    float var8 = CollideWithObstaclesPoly.move.x;
    float var9 = CollideWithObstaclesPoly.move.y;

      for (int var10 = 0; var10 < this.size(); var10++) {
    CCEdge var11 = this.get(var10);
         if (!var11.isPointOn(var1, var2) && !var11.isPointOn(var3, var4)) {
    float var12 = var11.normal.dot(CollideWithObstaclesPoly.move);
            if (!(var12 >= 0.01F)) {
    float var13 = var11.node1.x;
    float var14 = var11.node1.y;
    float var15 = var11.node2.x;
    float var16 = var11.node2.y;
    float var17 = var1 - var13;
    float var18 = var2 - var14;
    float var19 = var15 - var13;
    float var20 = var16 - var14;
    float var21 = 1.0F / (var20 * var8 - var19 * var9);
    float var22 = (var19 * var18 - var20 * var17) * var21;
               if (var22 >= 0.0F && var22 <= var7) {
    float var23 = (var18 * var8 - var17 * var9) * var21;
                  if (var23 >= 0.0F && var23 <= 1.0F) {
    float var24 = var1 + var22 * var8;
    float var25 = var2 + var22 * var9;
                     if (var5) {
                        this.render(var6);
                        LineDrawer.addRect(var24 - 0.05F, var25 - 0.05F, var11.node1.z, 0.1F, 0.1F, 1.0F, 1.0F, 1.0F);
                     }

    return true;
                  }
               }
            }
         }
      }

      return this.isPointInPolygon_WindingNumber((var1 + var3) / 2.0F, (var2 + var4) / 2.0F, 0) != EdgeRingHit.Outside;
   }

    void lineSegmentIntersect(float var1, float var2, float var3, float var4, ClosestPointOnEdge var5, bool var6) {
      CollideWithObstaclesPoly.move.set(var3 - var1, var4 - var2).normalize();

      for (int var7 = 0; var7 < this.size(); var7++) {
    CCEdge var8 = this.get(var7);
    float var9 = var8.normal.dot(CollideWithObstaclesPoly.move);
         if (!(var9 >= 0.0F)) {
    float var10 = var8.node1.x;
    float var11 = var8.node1.y;
    float var12 = var8.node2.x;
    float var13 = var8.node2.y;
    float var14 = var10 + 0.5F * (var12 - var10);
    float var15 = var11 + 0.5F * (var13 - var11);
            if (var6 && DebugOptions.instance.CollideWithObstaclesRenderNormals.getValue()) {
               LineDrawer.addLine(var14, var15, var8.node1.z, var14 + var8.normal.x, var15 + var8.normal.y, var8.node1.z, 0.0F, 0.0F, 1.0F, nullptr, true);
            }

    double var16 = (var13 - var11) * (var3 - var1) - (var12 - var10) * (var4 - var2);
            if (var16 != 0.0) {
    double var18 = ((var12 - var10) * (var2 - var11) - (var13 - var11) * (var1 - var10)) / var16;
    double var20 = ((var3 - var1) * (var2 - var11) - (var4 - var2) * (var1 - var10)) / var16;
               if (var18 >= 0.0 && var18 <= 1.0 && var20 >= 0.0 && var20 <= 1.0) {
                  if (var20 < 0.01 || var20 > 0.99) {
    CCNode var22 = var20 < 0.01 ? var8.node1 : var8.node2;
    double var23 = IsoUtils.DistanceToSquared(var1, var2, var22.x, var22.y);
                     if (var23 >= var5.distSq) {
                        continue;
                     }

                     if (var22.getNormalAndEdgeVectors(CollideWithObstaclesPoly.nodeNormal, CollideWithObstaclesPoly.edgeVec)) {
                        if (!(
                           CollideWithObstaclesPoly.nodeNormal.dot(CollideWithObstaclesPoly.move) + 0.05F
                              >= CollideWithObstaclesPoly.nodeNormal.dot(CollideWithObstaclesPoly.edgeVec)
                        )) {
                           var5.edge = var8;
                           var5.node = var22;
                           var5.distSq = var23;
                        }
                        continue;
                     }
                  }

    float var26 = (float)(var1 + var18 * (var3 - var1));
    float var27 = (float)(var2 + var18 * (var4 - var2));
    double var24 = IsoUtils.DistanceToSquared(var1, var2, var26, var27);
                  if (var24 < var5.distSq) {
                     var5.edge = var8;
                     var5.node = nullptr;
                     var5.distSq = var24;
                  }
               }
            }
         }
      }
   }

    void getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
      for (int var4 = 0; var4 < this.size(); var4++) {
    CCEdge var5 = this.get(var4);
         var5.getClosestPointOnEdge(var1, var2, var3);
      }
   }

    void render(bool var1) {
      if (!this.empty()) {
    float var2 = 0.0F;
    float var3 = var1 ? 1.0F : 0.5F;
    float var4 = var1 ? 0.0F : 0.5F;
    Vector3fObjectPool var5 = (Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get();

    for (auto& var7 : this)    CCNode var8 = var7.node1;
    CCNode var9 = var7.node2;
            LineDrawer.addLine(var8.x, var8.y, var8.z, var9.x, var9.y, var9.z, var2, var3, var4, nullptr, true);
    bool var10 = false;
            if (var10) {
    Vector3f var11 = ((Vector3f)var5.alloc()).set(var9.x - var8.x, var9.y - var8.y, var9.z - var8.z).normalize();
    Vector3f var12 = ((Vector3f)var5.alloc()).set(var11).cross(0.0F, 0.0F, 1.0F).normalize();
               var11.mul(0.9F);
               LineDrawer.addLine(
                  var9.x - var11.x * 0.1F - var12.x * 0.1F,
                  var9.y - var11.y * 0.1F - var12.y * 0.1F,
                  var9.z,
                  var9.x,
                  var9.y,
                  var9.z,
                  var2,
                  var3,
                  var4,
                  nullptr,
                  true
               );
               LineDrawer.addLine(
                  var9.x - var11.x * 0.1F + var12.x * 0.1F,
                  var9.y - var11.y * 0.1F + var12.y * 0.1F,
                  var9.z,
                  var9.x,
                  var9.y,
                  var9.z,
                  var2,
                  var3,
                  var4,
                  nullptr,
                  true
               );
               var5.release(var11);
               var5.release(var12);
            }
         }

    CCNode var13 = this.get(0).node1;
         LineDrawer.addRect(var13.x - 0.1F, var13.y - 0.1F, var13.z, 0.2F, 0.2F, 1.0F, 0.0F, 0.0F);
      }
   }

    static void releaseAll(std::vector<CollideWithObstaclesPoly$CCEdgeRing> var0) {
      pool.releaseAll(var0);
   }
}
} // namespace vehicles
} // namespace zombie
