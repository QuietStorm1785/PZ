#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Connection.h"
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/Obstacle.h"
#include "zombie/vehicles/PolygonalMap2/Square.h"
#include "zombie/vehicles/PolygonalMap2/VisibilityGraph.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    static int nextID = 1;
    const int ID;
    float x;
    float y;
    int z;
    bool ignore;
    Square square;
   std::vector<VisibilityGraph> graphs;
   const std::vector<Edge> edges = std::make_unique<std::vector<>>();
   const std::vector<Connection> visible = std::make_unique<std::vector<>>();
    int flags = 0;
   static const std::vector<Obstacle> tempObstacles = std::make_unique<std::vector<>>();
   static const ArrayDeque<PolygonalMap2$Node> pool = std::make_unique<ArrayDeque<>>();

   PolygonalMap2$Node() {
      this.ID = nextID++;
   }

   PolygonalMap2$Node init(float var1, float var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.ignore = false;
      this.square = nullptr;
      if (this.graphs != nullptr) {
         this.graphs.clear();
      }

      this.edges.clear();
      this.visible.clear();
      this.flags = 0;
    return this;
   }

   PolygonalMap2$Node init(Square var1) {
      this.x = var1.x + 0.5F;
      this.y = var1.y + 0.5F;
      this.z = var1.z;
      this.ignore = false;
      this.square = var1;
      if (this.graphs != nullptr) {
         this.graphs.clear();
      }

      this.edges.clear();
      this.visible.clear();
      this.flags = 0;
    return this;
   }

   PolygonalMap2$Node setXY(float var1, float var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }

    void addGraph(VisibilityGraph var1) {
      if (this.graphs == nullptr) {
         this.graphs = std::make_unique<std::vector<>>();
      }

      if (!$assertionsDisabled && this.graphs.contains(var1)) {
         throw std::make_unique<AssertionError>();
      } else {
         this.graphs.push_back(var1);
      }
   }

    bool sharesEdge(PolygonalMap2$Node var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
    Edge var3 = this.edges.get(var2);
         if (var3.hasNode(var1)) {
    return true;
         }
      }

    return false;
   }

    bool sharesShape(PolygonalMap2$Node var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
    Edge var3 = this.edges.get(var2);

         for (int var4 = 0; var4 < var1.edges.size(); var4++) {
    Edge var5 = var1.edges.get(var4);
            if (var3.obstacle != nullptr && var3.obstacle == var5.obstacle) {
    return true;
            }
         }
      }

    return false;
   }

    void getObstacles(std::vector<Obstacle> var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
    Edge var3 = this.edges.get(var2);
         if (!var1.contains(var3.obstacle)) {
            var1.push_back(var3.obstacle);
         }
      }
   }

    bool onSameShapeButDoesNotShareAnEdge(PolygonalMap2$Node var1) {
      tempObstacles.clear();
      this.getObstacles(tempObstacles);

      for (int var2 = 0; var2 < tempObstacles.size(); var2++) {
    Obstacle var3 = tempObstacles.get(var2);
         if (var3.hasNode(var1) && !var3.hasAdjacentNodes(this, var1)) {
    return true;
         }
      }

    return false;
   }

    bool hasFlag(int var1) {
      return (this.flags & var1) != 0;
   }

    bool isConnectedTo(PolygonalMap2$Node var1) {
      if (this.hasFlag(4)) {
    return true;
      } else {
         for (int var2 = 0; var2 < this.visible.size(); var2++) {
    Connection var3 = this.visible.get(var2);
            if (var3.node1 == var1 || var3.node2 == var1) {
    return true;
            }
         }

    return false;
      }
   }

   static PolygonalMap2$Node alloc() {
      if (pool.empty()) {
    bool var0 = false;
      } else {
    bool var1 = false;
      }

      return pool.empty() ? new PolygonalMap2$Node() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         for (int var1 = this.visible.size() - 1; var1 >= 0; var1--) {
            PolygonalMap2.instance.breakConnection(this.visible.get(var1));
         }

         pool.push(this);
      }
   }

    static void releaseAll(std::vector<PolygonalMap2$Node> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         ((PolygonalMap2$Node)var0.get(var1)).release();
      }
   }
}
} // namespace vehicles
} // namespace zombie
