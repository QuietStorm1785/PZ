#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/vehicles/PolygonalMap2/AdjustStartEndNodeData.h"
#include "zombie/vehicles/PolygonalMap2/ClosestPointOnEdge.h"
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/EdgeRing.h"
#include "zombie/vehicles/PolygonalMap2/EdgeRingHit.h"
#include "zombie/vehicles/PolygonalMap2/ImmutableRectF.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/Vehicle.h"
#include "zombie/vehicles/PolygonalMap2/VisibilityGraph.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Vehicle vehicle;
    const EdgeRing outer = std::make_shared<EdgeRing>();
   const std::vector<EdgeRing> inner = std::make_unique<std::vector<>>();
    ImmutableRectF bounds;
    Node nodeCrawlFront;
    Node nodeCrawlRear;
   const std::vector<Node> crawlNodes = std::make_unique<std::vector<>>();
   static const ArrayDeque<PolygonalMap2$Obstacle> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$Obstacle() {
   }

   PolygonalMap2$Obstacle init(Vehicle var1) {
      this.vehicle = var1;
      this.outer.clear();
      this.inner.clear();
      this.nodeCrawlFront = this.nodeCrawlRear = nullptr;
      this.crawlNodes.clear();
    return this;
   }

   PolygonalMap2$Obstacle init(IsoGridSquare var1) {
      this.vehicle = nullptr;
      this.outer.clear();
      this.inner.clear();
      this.nodeCrawlFront = this.nodeCrawlRear = nullptr;
      this.crawlNodes.clear();
    return this;
   }

    bool hasNode(Node var1) {
      if (this.outer.hasNode(var1)) {
    return true;
      } else {
         for (int var2 = 0; var2 < this.inner.size(); var2++) {
    EdgeRing var3 = this.inner.get(var2);
            if (var3.hasNode(var1)) {
    return true;
            }
         }

    return false;
      }
   }

    bool hasAdjacentNodes(Node var1, Node var2) {
      if (this.outer.hasAdjacentNodes(var1, var2)) {
    return true;
      } else {
         for (int var3 = 0; var3 < this.inner.size(); var3++) {
    EdgeRing var4 = this.inner.get(var3);
            if (var4.hasAdjacentNodes(var1, var2)) {
    return true;
            }
         }

    return false;
      }
   }

    bool isPointInside(float var1, float var2, int var3) {
      if (this.outer.isPointInPolygon_WindingNumber(var1, var2, var3) != EdgeRingHit.Inside) {
    return false;
      } else if (this.inner.empty()) {
    return true;
      } else {
         for (int var4 = 0; var4 < this.inner.size(); var4++) {
    EdgeRing var5 = this.inner.get(var4);
            if (var5.isPointInPolygon_WindingNumber(var1, var2, var3) != EdgeRingHit.Outside) {
    return false;
            }
         }

    return true;
      }
   }

    bool isPointInside(float var1, float var2) {
    uint8_t var3 = 0;
      return this.isPointInside(var1, var2, var3);
   }

    bool lineSegmentIntersects(float var1, float var2, float var3, float var4) {
      if (this.outer.lineSegmentIntersects(var1, var2, var3, var4)) {
    return true;
      } else {
         for (int var5 = 0; var5 < this.inner.size(); var5++) {
    EdgeRing var6 = this.inner.get(var5);
            if (var6.lineSegmentIntersects(var1, var2, var3, var4)) {
    return true;
            }
         }

    return false;
      }
   }

    bool isNodeInsideOf(Node var1) {
      if (this.hasNode(var1)) {
    return false;
      } else {
         return !this.bounds.containsPoint(var1.x, var1.y) ? false : this.isPointInside(var1.x, var1.y);
      }
   }

    void getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
      var3.edge = nullptr;
      var3.node = nullptr;
      var3.distSq = double.MAX_VALUE;
      this.outer.getClosestPointOnEdge(var1, var2, var3);

      for (int var4 = 0; var4 < this.inner.size(); var4++) {
    EdgeRing var5 = this.inner.get(var4);
         var5.getClosestPointOnEdge(var1, var2, var3);
      }
   }

    bool splitEdgeAtNearestPoint(ClosestPointOnEdge var1, int var2, AdjustStartEndNodeData var3) {
      if (var1.edge == nullptr) {
    return false;
      } else {
         var3.obstacle = this;
         if (var1.node == nullptr) {
            var3.node = Node.alloc().init(var1.point.x, var1.point.y, var2);
            var3.newEdge = var1.edge.split(var3.node);
            var3.isNodeNew = true;
         } else {
            var3.node = var1.node;
            var3.newEdge = nullptr;
            var3.isNodeNew = false;
         }

    return true;
      }
   }

    void unsplit(Node var1, std::vector<Edge> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
    Edge var4 = (Edge)var2.get(var3);
         if (var4.node1 == var1) {
            if (var3 > 0) {
    Edge var5 = (Edge)var2.get(var3 - 1);
               var5.node2 = var4.node2;
               if (!$assertionsDisabled && !var4.node2.edges.contains(var4)) {
                  throw std::make_unique<AssertionError>();
               }

               var4.node2.edges.remove(var4);
               if (!$assertionsDisabled && var4.node2.edges.contains(var5)) {
                  throw std::make_unique<AssertionError>();
               }

               var4.node2.edges.push_back(var5);
               PolygonalMap2.instance.connectTwoNodes(var5.node1, var5.node2);
            } else {
               ((Edge)var2.get(var3 + 1)).node1 = ((Edge)var2.get(var2.size() - 1)).node2;
            }

            var4.release();
            var2.remove(var3);
            break;
         }
      }
   }

    void calcBounds() {
    float var1 = float.MAX_VALUE;
    float var2 = float.MAX_VALUE;
    float var3 = float.MIN_VALUE;
    float var4 = float.MIN_VALUE;

      for (int var5 = 0; var5 < this.outer.size(); var5++) {
    Edge var6 = (Edge)this.outer.get(var5);
         var1 = Math.min(var1, var6.node1.x);
         var2 = Math.min(var2, var6.node1.y);
         var3 = Math.max(var3, var6.node1.x);
         var4 = Math.max(var4, var6.node1.y);
      }

      if (this.bounds != nullptr) {
         this.bounds.release();
      }

    float var7 = 0.01F;
      this.bounds = ImmutableRectF.alloc().init(var1 - var7, var2 - var7, var3 - var1 + var7 * 2.0F, var4 - var2 + var7 * 2.0F);
   }

    void render(std::vector<Edge> var1, bool var2) {
      if (!var1.empty()) {
    float var3 = 0.0F;
    float var4 = var2 ? 1.0F : 0.5F;
    float var5 = var2 ? 0.0F : 0.5F;

    for (auto& var7 : var1)    Node var8 = var7.node1;
    Node var9 = var7.node2;
            LineDrawer.addLine(var8.x, var8.y, var8.z, var9.x, var9.y, var9.z, var3, var4, var5, nullptr, true);
    Vector3f var10 = std::make_shared<Vector3f>(var9.x - var8.x, var9.y - var8.y, var9.z - var8.z).normalize();
    Vector3f var11 = std::make_shared<Vector3f>(var10).cross(0.0F, 0.0F, 1.0F).normalize();
            var10.mul(0.9F);
            LineDrawer.addLine(
               var9.x - var10.x * 0.1F - var11.x * 0.1F, var9.y - var10.y * 0.1F - var11.y * 0.1F, var9.z, var9.x, var9.y, var9.z, var3, var4, var5, nullptr, true
            );
            LineDrawer.addLine(
               var9.x - var10.x * 0.1F + var11.x * 0.1F, var9.y - var10.y * 0.1F + var11.y * 0.1F, var9.z, var9.x, var9.y, var9.z, var3, var4, var5, nullptr, true
            );
            var3 = 1.0F - var3;
         }

    Node var12 = ((Edge)var1.get(0)).node1;
         LineDrawer.addLine(var12.x - 0.1F, var12.y - 0.1F, var12.z, var12.x + 0.1F, var12.y + 0.1F, var12.z, 1.0F, 0.0F, 0.0F, nullptr, false);
      }
   }

    void render() {
      this.render(this.outer, true);

      for (int var1 = 0; var1 < this.inner.size(); var1++) {
         this.render((std::vector<Edge>)this.inner.get(var1), false);
      }
   }

    void connectCrawlNodes(VisibilityGraph var1, PolygonalMap2$Obstacle var2) {
      this.connectCrawlNode(var1, var2, this.nodeCrawlFront, var2.nodeCrawlFront);
      this.connectCrawlNode(var1, var2, this.nodeCrawlFront, var2.nodeCrawlRear);
      this.connectCrawlNode(var1, var2, this.nodeCrawlRear, var2.nodeCrawlFront);
      this.connectCrawlNode(var1, var2, this.nodeCrawlRear, var2.nodeCrawlRear);

      for (byte var3 = 0; var3 < this.crawlNodes.size(); var3 += 3) {
    Node var4 = this.crawlNodes.get(var3);
    Node var5 = this.crawlNodes.get(var3 + 2);

         for (byte var6 = 0; var6 < var2.crawlNodes.size(); var6 += 3) {
    Node var7 = var2.crawlNodes.get(var6);
    Node var8 = var2.crawlNodes.get(var6 + 2);
            this.connectCrawlNode(var1, var2, var4, var7);
            this.connectCrawlNode(var1, var2, var4, var8);
            this.connectCrawlNode(var1, var2, var5, var7);
            this.connectCrawlNode(var1, var2, var5, var8);
         }
      }
   }

    void connectCrawlNode(VisibilityGraph var1, PolygonalMap2$Obstacle var2, Node var3, Node var4) {
      if (this.isNodeInsideOf(var4)) {
         var4.flags |= 2;
         var3 = this.getClosestInteriorCrawlNode(var4.x, var4.y);
         if (var3 != nullptr) {
            if (!var3.isConnectedTo(var4)) {
               PolygonalMap2.instance.connectTwoNodes(var3, var4);
            }
         }
      } else if (!var3.ignore && !var4.ignore) {
         if (!var3.isConnectedTo(var4)) {
            if (var1.isVisible(var3, var4)) {
               PolygonalMap2.instance.connectTwoNodes(var3, var4);
            }
         }
      }
   }

    Node getClosestInteriorCrawlNode(float var1, float var2) {
    Node var3 = nullptr;
    float var4 = float.MAX_VALUE;

      for (byte var5 = 0; var5 < this.crawlNodes.size(); var5 += 3) {
    Node var6 = this.crawlNodes.get(var5 + 1);
    float var7 = IsoUtils.DistanceToSquared(var6.x, var6.y, var1, var2);
         if (var7 < var4) {
            var3 = var6;
            var4 = var7;
         }
      }

    return var3;
   }

   static PolygonalMap2$Obstacle alloc() {
      return pool.empty() ? new PolygonalMap2$Obstacle() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         this.outer.release();
         this.outer.clear();
         EdgeRing.releaseAll(this.inner);
         this.inner.clear();
         pool.push(this);
      }
   }

    static void releaseAll(std::vector<PolygonalMap2$Obstacle> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         ((PolygonalMap2$Obstacle)var0.get(var1)).release();
      }
   }
}
} // namespace vehicles
} // namespace zombie
