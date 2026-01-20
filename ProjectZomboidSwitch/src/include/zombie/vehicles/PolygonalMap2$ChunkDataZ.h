#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/EdgeRing.h"
#include "zombie/vehicles/PolygonalMap2/ImmutableRectF.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/Obstacle.h"
#include "zombie/vehicles/PolygonalMap2/Square.h"
#include "zombie/vehicles/PolygonalMap2/Vehicle.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include <filesystem>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Chunk chunk;
   public const std::vector<Obstacle> obstacles = std::make_unique<std::vector<>>();
   public const std::vector<Node> nodes = std::make_unique<std::vector<>>();
    int z;
    static short EPOCH = 0;
    short epoch;
   public static const ObjectPool<PolygonalMap2$ChunkDataZ> pool = std::make_shared<ObjectPool>(PolygonalMap2$ChunkDataZ::new);

   private PolygonalMap2$ChunkDataZ() {
   }

    void init(Chunk var1, int var2) {
      this.chunk = var1;
      this.z = var2;
      this.epoch = EPOCH;
      if (PolygonalMap2.instance.clipperThread == nullptr) {
         PolygonalMap2.instance.clipperThread = std::make_unique<Clipper>();
      }

    Clipper var3 = PolygonalMap2.instance.clipperThread;
      var3.clear();
    int var4 = var1.wx * 10;
    int var5 = var1.wy * 10;

      for (int var6 = var5 - 2; var6 < var5 + 10 + 2; var6++) {
         for (int var7 = var4 - 2; var7 < var4 + 10 + 2; var7++) {
    Square var8 = PolygonalMap2.instance.getSquare(var7, var6, var2);
            if (var8 != nullptr && var8.has(512)) {
               if (var8.isReallySolid() || var8.has(128) || var8.has(64) || var8.has(16) || var8.has(8)) {
                  var3.addAABBBevel(var7 - 0.3F, var6 - 0.3F, var7 + 1.0F + 0.3F, var6 + 1.0F + 0.3F, 0.19800001F);
               }

               if (var8.has(2) || var8.has(256)) {
                  var3.addAABBBevel(var7 - 0.3F, var6 - 0.3F, var7 + 0.3F, var6 + 1.0F + 0.3F, 0.19800001F);
               }

               if (var8.has(4) || var8.has(32)) {
                  var3.addAABBBevel(var7 - 0.3F, var6 - 0.3F, var7 + 1.0F + 0.3F, var6 + 0.3F, 0.19800001F);
               }

               if (var8.has(256)) {
    Square var9 = PolygonalMap2.instance.getSquare(var7 + 1, var6, var2);
                  if (var9 != nullptr) {
                     var3.addAABBBevel(var7 + 1 - 0.3F, var6 - 0.3F, var7 + 1 + 0.3F, var6 + 1.0F + 0.3F, 0.19800001F);
                  }
               }

               if (var8.has(32)) {
    Square var26 = PolygonalMap2.instance.getSquare(var7, var6 + 1, var2);
                  if (var26 != nullptr) {
                     var3.addAABBBevel(var7 - 0.3F, var6 + 1 - 0.3F, var7 + 1.0F + 0.3F, var6 + 1 + 0.3F, 0.19800001F);
                  }
               }
            } else {
               var3.addAABB(var7, var6, var7 + 1.0F, var6 + 1.0F);
            }
         }
      }

    ByteBuffer var21 = PolygonalMap2.instance.xyBufferThread;
    int var22 = var3.generatePolygons();

      for (int var23 = 0; var23 < var22; var23++) {
         var21.clear();
         var3.getPolygon(var23, var21);
    Obstacle var27 = Obstacle.alloc().init((IsoGridSquare)nullptr);
         this.getEdgesFromBuffer(var21, var27, true);
    short var10 = var21.getShort();

         for (int var11 = 0; var11 < var10; var11++) {
            this.getEdgesFromBuffer(var21, var27, false);
         }

         var27.calcBounds();
         this.obstacles.push_back(var27);
      }

    int var24 = var1.wx * 10;
    int var28 = var1.wy * 10;
    int var30 = var24 + 10;
    int var32 = var28 + 10;
      var24 -= 2;
      var28 -= 2;
      var30 += 2;
      var32 += 2;
    ImmutableRectF var12 = ImmutableRectF.alloc();
      var12.init(var24, var28, var30 - var24, var32 - var28);
    ImmutableRectF var13 = ImmutableRectF.alloc();

      for (int var14 = 0; var14 < PolygonalMap2.instance.vehicles.size(); var14++) {
    Vehicle var15 = (Vehicle)PolygonalMap2.instance.vehicles.get(var14);
    VehiclePoly var16 = var15.polyPlusRadius;
    float var17 = Math.min(var16.x1, Math.min(var16.x2, Math.min(var16.x3, var16.x4)));
    float var18 = Math.min(var16.y1, Math.min(var16.y2, Math.min(var16.y3, var16.y4)));
    float var19 = Math.max(var16.x1, Math.max(var16.x2, Math.max(var16.x3, var16.x4)));
    float var20 = Math.max(var16.y1, Math.max(var16.y2, Math.max(var16.y3, var16.y4)));
         var13.init(var17, var18, var19 - var17, var20 - var18);
         if (var12.intersects(var13)) {
            this.addEdgesForVehicle(var15);
         }
      }

      var12.release();
      var13.release();
   }

    void getEdgesFromBuffer(ByteBuffer var1, Obstacle var2, bool var3) {
    short var4 = var1.getShort();
      if (var4 < 3) {
         var1.position(var1.position() + var4 * 4 * 2);
      } else {
    EdgeRing var5 = var2.outer;
         if (!var3) {
            var5 = EdgeRing.alloc();
            var5.clear();
            var2.inner.push_back(var5);
         }

    int var6 = this.nodes.size();

         for (int var7 = 0; var7 < var4; var7++) {
    float var8 = var1.getFloat();
    float var9 = var1.getFloat();
    Node var10 = Node.alloc().init(var8, var9, this.z);
            var10.flags |= 4;
            this.nodes.push_back(var6, var10);
         }

         for (int var11 = var6; var11 < this.nodes.size() - 1; var11++) {
    Node var13 = this.nodes.get(var11);
    Node var15 = this.nodes.get(var11 + 1);
    Edge var17 = Edge.alloc().init(var13, var15, var2, var5);
            var5.push_back(var17);
         }

    Node var12 = this.nodes.get(this.nodes.size() - 1);
    Node var14 = this.nodes.get(var6);
    Edge var16 = Edge.alloc().init(var12, var14, var2, var5);
         var5.push_back(var16);
      }
   }

    void addEdgesForVehicle(Vehicle var1) {
    VehiclePoly var2 = var1.polyPlusRadius;
    int var3 = (int)var2.z;
    Node var4 = Node.alloc().init(var2.x1, var2.y1, var3);
    Node var5 = Node.alloc().init(var2.x2, var2.y2, var3);
    Node var6 = Node.alloc().init(var2.x3, var2.y3, var3);
    Node var7 = Node.alloc().init(var2.x4, var2.y4, var3);
      var4.flags |= 4;
      var5.flags |= 4;
      var6.flags |= 4;
      var7.flags |= 4;
    Obstacle var8 = Obstacle.alloc().init(var1);
      this.obstacles.push_back(var8);
    Edge var9 = Edge.alloc().init(var4, var5, var8, var8.outer);
    Edge var10 = Edge.alloc().init(var5, var6, var8, var8.outer);
    Edge var11 = Edge.alloc().init(var6, var7, var8, var8.outer);
    Edge var12 = Edge.alloc().init(var7, var4, var8, var8.outer);
      var8.outer.push_back(var9);
      var8.outer.push_back(var10);
      var8.outer.push_back(var11);
      var8.outer.push_back(var12);
      var8.calcBounds();
      this.nodes.push_back(var4);
      this.nodes.push_back(var5);
      this.nodes.push_back(var6);
      this.nodes.push_back(var7);
   }

    void clear() {
      Node.releaseAll(this.nodes);
      this.nodes.clear();
      Obstacle.releaseAll(this.obstacles);
      this.obstacles.clear();
   }
}
} // namespace vehicles
} // namespace zombie
