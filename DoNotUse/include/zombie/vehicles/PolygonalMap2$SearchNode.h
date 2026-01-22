#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ASearchNode.h"
#include "astar/ISearchNode.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/vehicles/PolygonalMap2/Connection.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/Square.h"
#include "zombie/vehicles/PolygonalMap2/VGAStar.h"
#include "zombie/vehicles/PolygonalMap2/VisibilityGraph.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    VGAStar astar;
    Node vgNode;
    Square square;
    int tx;
    int ty;
   PolygonalMap2$SearchNode parent;
    static int nextID = 1;
    int ID = nextID++;
    static const double SQRT2 = Math.sqrt(2.0);
   static const ArrayDeque<PolygonalMap2$SearchNode> pool = std::make_unique<ArrayDeque<>>();

   PolygonalMap2$SearchNode init(VGAStar var1, Node var2) {
      this.setG(0.0);
      this.astar = var1;
      this.vgNode = var2;
      this.square = nullptr;
      this.tx = this.ty = -1;
      this.parent = nullptr;
    return this;
   }

   PolygonalMap2$SearchNode init(VGAStar var1, Square var2) {
      this.setG(0.0);
      this.astar = var1;
      this.vgNode = nullptr;
      this.square = var2;
      this.tx = this.ty = -1;
      this.parent = nullptr;
    return this;
   }

   PolygonalMap2$SearchNode init(VGAStar var1, int var2, int var3) {
      this.setG(0.0);
      this.astar = var1;
      this.vgNode = nullptr;
      this.square = nullptr;
      this.tx = var2;
      this.ty = var3;
      this.parent = nullptr;
    return this;
   }

    double h() {
      return this.dist(this.astar.goalNode.searchNode);
   }

    double c(ISearchNode var1) {
      PolygonalMap2$SearchNode var2 = (PolygonalMap2$SearchNode)var1;
    double var3 = 0.0;
    bool var5 = this.astar.dynamic_cast<IsoZombie*>(mover) != nullptr && ((IsoZombie)this.astar.mover).bCrawling;
    bool var6 = !(this.astar.dynamic_cast<IsoZombie*>(mover) != nullptr) || ((IsoZombie)this.astar.mover).bCrawling;
      if (var6 && this.square != nullptr && var2.square != nullptr) {
         if (this.square.x == var2.square.x - 1 && this.square.y == var2.square.y) {
            if (var2.square.has(2048)) {
               var3 = !var5 && var2.square.has(1048576) ? 20.0 : 200.0;
            }
         } else if (this.square.x == var2.square.x + 1 && this.square.y == var2.square.y) {
            if (this.square.has(2048)) {
               var3 = !var5 && this.square.has(1048576) ? 20.0 : 200.0;
            }
         } else if (this.square.y == var2.square.y - 1 && this.square.x == var2.square.x) {
            if (var2.square.has(4096)) {
               var3 = !var5 && var2.square.has(2097152) ? 20.0 : 200.0;
            }
         } else if (this.square.y == var2.square.y + 1 && this.square.x == var2.square.x && this.square.has(4096)) {
            var3 = !var5 && this.square.has(2097152) ? 20.0 : 200.0;
         }
      }

      if (var2.square != nullptr && var2.square.has(131072)) {
         var3 = 20.0;
      }

      if (this.vgNode != nullptr && var2.vgNode != nullptr) {
         for (int var7 = 0; var7 < this.vgNode.visible.size(); var7++) {
    Connection var8 = (Connection)this.vgNode.visible.get(var7);
            if (var8.otherNode(this.vgNode) == var2.vgNode) {
               if ((this.vgNode.square == nullptr || !this.vgNode.square.has(131072)) && var8.has(2)) {
                  var3 = 20.0;
               }
               break;
            }
         }
      }

    Square var9 = this.square == nullptr ? PolygonalMap2.instance.getSquare((int)this.vgNode.x, (int)this.vgNode.y, 0) : this.square;
    Square var11 = var2.square == nullptr ? PolygonalMap2.instance.getSquare((int)var2.vgNode.x, (int)var2.vgNode.y, 0) : var2.square;
      if (var9 != nullptr && var11 != nullptr) {
         if (var9.x == var11.x - 1 && var9.y == var11.y) {
            if (var11.has(32768)) {
               var3 = 20.0;
            }
         } else if (var9.x == var11.x + 1 && var9.y == var11.y) {
            if (var9.has(32768)) {
               var3 = 20.0;
            }
         } else if (var9.y == var11.y - 1 && var9.x == var11.x) {
            if (var11.has(65536)) {
               var3 = 20.0;
            }
         } else if (var9.y == var11.y + 1 && var9.x == var11.x && var9.has(65536)) {
            var3 = 20.0;
         }

         if (var5) {
            if (var9.x == var11.x - 1 && var9.y == var11.y) {
               if (var11.has(2) && var11.has(8192)) {
                  var3 = 20.0;
               }
            } else if (var9.x == var11.x + 1 && var9.y == var11.y) {
               if (var9.has(2) && var9.has(8192)) {
                  var3 = 20.0;
               }
            } else if (var9.y == var11.y - 1 && var9.x == var11.x) {
               if (var11.has(4) && var11.has(16384)) {
                  var3 = 20.0;
               }
            } else if (var9.y == var11.y + 1 && var9.x == var11.x && var9.has(4) && var9.has(16384)) {
               var3 = 20.0;
            }
         }
      }

    bool var10 = this.vgNode != nullptr && this.vgNode.hasFlag(2);
    bool var12 = var2.vgNode != nullptr && var2.vgNode.hasFlag(2);
      if (!var10 && var12 && !this.astar.bIgnoreCrawlCost) {
         var3 += 10.0;
      }

      if (var2.square != nullptr) {
         var3 += var2.square.cost;
      }

      return this.dist(var2) + var3;
   }

    void getSuccessors(std::vector<ISearchNode> var1) {
    std::vector var2 = var1;
      if (this.vgNode != nullptr) {
         if (this.vgNode.graphs != nullptr) {
            for (int var3 = 0; var3 < this.vgNode.graphs.size(); var3++) {
    VisibilityGraph var4 = (VisibilityGraph)this.vgNode.graphs.get(var3);
               if (!var4.created) {
                  var4.create();
               }
            }
         }

         for (int var8 = 0; var8 < this.vgNode.visible.size(); var8++) {
    Connection var14 = (Connection)this.vgNode.visible.get(var8);
    Node var5 = var14.otherNode(this.vgNode);
            PolygonalMap2$SearchNode var6 = this.astar.getSearchNode(var5);
            if ((this.vgNode.square == nullptr || var6.square == nullptr || !this.astar.isKnownBlocked(this.vgNode.square, var6.square))
               && (this.astar.bCanCrawl || !var5.hasFlag(2))
               && (this.astar.bCanThump || !var14.has(2))) {
               var2.push_back(var6);
            }
         }

         if (!this.vgNode.hasFlag(8)) {
            return;
         }
      }

      if (this.square != nullptr) {
         for (int var9 = -1; var9 <= 1; var9++) {
            for (int var15 = -1; var15 <= 1; var15++) {
               if (var15 != 0 || var9 != 0) {
    Square var20 = PolygonalMap2.instance.getSquare(this.square.x + var15, this.square.y + var9, this.square.z);
                  if (var20 != nullptr && !this.astar.isSquareInCluster(var20) && !this.astar.canNotMoveBetween(this.square, var20, false)) {
                     PolygonalMap2$SearchNode var25 = this.astar.getSearchNode(var20);
                     if (var2.contains(var25)) {
    bool var7 = false;
                     } else {
                        var2.push_back(var25);
                     }
                  }
               }
            }
         }

         if (this.square.z > 0) {
    Square var10 = PolygonalMap2.instance.getSquare(this.square.x, this.square.y + 1, this.square.z - 1);
            if (var10 != nullptr && var10.has(64) && !this.astar.isSquareInCluster(var10)) {
               PolygonalMap2$SearchNode var16 = this.astar.getSearchNode(var10);
               if (var2.contains(var16)) {
    bool var21 = false;
               } else {
                  var2.push_back(var16);
               }
            }

            var10 = PolygonalMap2.instance.getSquare(this.square.x + 1, this.square.y, this.square.z - 1);
            if (var10 != nullptr && var10.has(8) && !this.astar.isSquareInCluster(var10)) {
               PolygonalMap2$SearchNode var17 = this.astar.getSearchNode(var10);
               if (var2.contains(var17)) {
    bool var22 = false;
               } else {
                  var2.push_back(var17);
               }
            }
         }

         if (this.square.z < 8 && this.square.has(64)) {
    Square var12 = PolygonalMap2.instance.getSquare(this.square.x, this.square.y - 1, this.square.z + 1);
            if (var12 != nullptr && !this.astar.isSquareInCluster(var12)) {
               PolygonalMap2$SearchNode var18 = this.astar.getSearchNode(var12);
               if (var2.contains(var18)) {
    bool var23 = false;
               } else {
                  var2.push_back(var18);
               }
            }
         }

         if (this.square.z < 8 && this.square.has(8)) {
    Square var13 = PolygonalMap2.instance.getSquare(this.square.x - 1, this.square.y, this.square.z + 1);
            if (var13 != nullptr && !this.astar.isSquareInCluster(var13)) {
               PolygonalMap2$SearchNode var19 = this.astar.getSearchNode(var13);
               if (var2.contains(var19)) {
    bool var24 = false;
               } else {
                  var2.push_back(var19);
               }
            }
         }
      }
   }

    ISearchNode getParent() {
      return this.parent;
   }

    void setParent(ISearchNode var1) {
      this.parent = (PolygonalMap2$SearchNode)var1;
   }

    int keyCode() {
      return this.ID;
   }

    float getX() {
      if (this.square != nullptr) {
         return this.square.x + 0.5F;
      } else {
         return this.vgNode != nullptr ? this.vgNode.x : this.tx;
      }
   }

    float getY() {
      if (this.square != nullptr) {
         return this.square.y + 0.5F;
      } else {
         return this.vgNode != nullptr ? this.vgNode.y : this.ty;
      }
   }

    float getZ() {
      if (this.square != nullptr) {
         return this.square.z;
      } else {
         return this.vgNode != nullptr ? this.vgNode.z : 0.0F;
      }
   }

    double dist(PolygonalMap2$SearchNode var1) {
      if (this.square == nullptr || var1.square == nullptr || Math.abs(this.square.x - var1.square.x) > 1 || Math.abs(this.square.y - var1.square.y) > 1) {
    float var2 = this.getX();
    float var3 = this.getY();
    float var4 = var1.getX();
    float var5 = var1.getY();
         return Math.sqrt(Math.pow(var2 - var4, 2.0) + Math.pow(var3 - var5, 2.0));
      } else {
         return this.square.x != var1.square.x && this.square.y != var1.square.y ? SQRT2 : 1.0;
      }
   }

    float getApparentZ() {
      if (this.square == nullptr) {
         return this.vgNode.z;
      } else if (this.square.has(8) || this.square.has(64)) {
         return this.square.z + 0.75F;
      } else if (this.square.has(16) || this.square.has(128)) {
         return this.square.z + 0.5F;
      } else {
         return !this.square.has(32) && !this.square.has(256) ? this.square.z : this.square.z + 0.25F;
      }
   }

   static PolygonalMap2$SearchNode alloc() {
      return pool.empty() ? new PolygonalMap2$SearchNode() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
