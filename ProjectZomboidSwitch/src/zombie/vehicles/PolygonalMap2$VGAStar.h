#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "AstarCpp/AStar.h"
#include "astar/ISearchNode.h"
#if __has_include(<absl/container/flat_hash_map.h>)
#  include <absl/container/flat_hash_map.h>
#  define INT_HASH_MAP absl::flat_hash_map
#elif __has_include(<boost/unordered_map.hpp>)
#  include <boost/unordered_map.hpp>
#  define INT_HASH_MAP boost::unordered_map
#else
#  include <unordered_map>
#  define INT_HASH_MAP std::unordered_map
#endif
#include "zombie/ai/KnownBlockedEdges.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/vehicles/PolygonalMap2/GoalNode.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/PathFindRequest.h"
#include "zombie/vehicles/PolygonalMap2/SearchNode.h"
#include "zombie/vehicles/PolygonalMap2/Square.h"
#include "zombie/vehicles/PolygonalMap2/VGAStar/InitProc.h"
#include "zombie/vehicles/PolygonalMap2/VisibilityGraph.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
   std::vector<VisibilityGraph> graphs;
   const std::vector<SearchNode> searchNodes = std::make_unique<std::vector<>>();
   INT_HASH_MAP<int, SearchNode> nodeMap;
    const GoalNode goalNode = std::make_shared<GoalNode>();
   INT_HASH_MAP<int, SearchNode> squareToNode;
    Mover mover;
    bool bCanCrawl;
    bool bIgnoreCrawlCost;
    bool bCanThump;
   INT_HASH_MAP<int, KnownBlockedEdges> knownBlockedEdges;
    const InitProc initProc = std::make_shared<InitProc>(this);

   private PolygonalMap2$VGAStar() {
   }

   PolygonalMap2$VGAStar init(std::vector<VisibilityGraph> var1, TIntObjectHashMap<Node> var2) {
      this.setMaxSteps(5000);
      this.graphs = var1;
      this.searchNodes.clear();
      this.nodeMap.clear();
      this.squareToNode.clear();
      this.mover = nullptr;
      var2.forEachEntry(this.initProc);
    return this;
   }

    VisibilityGraph getVisGraphForSquare(Square var1) {
      for (int var2 = 0; var2 < this.graphs.size(); var2++) {
    VisibilityGraph var3 = this.graphs.get(var2);
         if (var3.contains(var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    bool isSquareInCluster(Square var1) {
      return this.getVisGraphForSquare(var1) != nullptr;
   }

    SearchNode getSearchNode(Node var1) {
      if (var1.square != nullptr) {
         return this.getSearchNode(var1.square);
      } else {
    SearchNode var2 = (SearchNode)this.nodeMap.get(var1.ID);
         if (var2 == nullptr) {
            var2 = SearchNode.alloc().init(this, var1);
            this.searchNodes.push_back(var2);
            this.nodeMap.put(var1.ID, var2);
         }

    return var2;
      }
   }

    SearchNode getSearchNode(Square var1) {
    SearchNode var2 = (SearchNode)this.squareToNode.get(var1.ID);
      if (var2 == nullptr) {
         var2 = SearchNode.alloc().init(this, var1);
         this.searchNodes.push_back(var2);
         this.squareToNode.put(var1.ID, var2);
      }

    return var2;
   }

    SearchNode getSearchNode(int var1, int var2) {
    SearchNode var3 = SearchNode.alloc().init(this, var1, var2);
      this.searchNodes.push_back(var3);
    return var3;
   }

   std::vector<ISearchNode> shortestPath(PathFindRequest var1, SearchNode var2, SearchNode var3) {
      this.mover = var1.mover;
      this.bCanCrawl = var1.bCanCrawl;
      this.bIgnoreCrawlCost = var1.bIgnoreCrawlCost;
      this.bCanThump = var1.bCanThump;
      this.goalNode.init(var3);
      return this.shortestPath(var2, this.goalNode);
   }

    bool canNotMoveBetween(Square var1, Square var2, bool var3) {
      if (!$assertionsDisabled && Math.abs(var1.x - var2.x) > 1) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && Math.abs(var1.y - var2.y) > 1) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && var1.z != var2.z) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && var1 == var2) {
         throw std::make_unique<AssertionError>();
      } else {
         if (var1.x == 10921 && var1.y == 10137 && var2.x == var1.x - 1 && var2.y == var1.y) {
    bool var4 = true;
         }

    bool var17 = var2.x < var1.x;
    bool var5 = var2.x > var1.x;
    bool var6 = var2.y < var1.y;
    bool var7 = var2.y > var1.y;
         if (!var2.isNonThumpableSolid() && (this.bCanThump || !var2.isReallySolid())) {
            if (var2.y < var1.y && var1.has(64)) {
    return true;
            } else if (var2.x < var1.x && var1.has(8)) {
    return true;
            } else if (var2.y > var1.y && var2.x == var1.x && var2.has(64)) {
    return true;
            } else if (var2.x > var1.x && var2.y == var1.y && var2.has(8)) {
    return true;
            } else if (var2.x != var1.x && var2.has(448)) {
    return true;
            } else if (var2.y != var1.y && var2.has(56)) {
    return true;
            } else if (var2.x != var1.x && var1.has(448)) {
    return true;
            } else if (var2.y != var1.y && var1.has(56)) {
    return true;
            } else if (!var2.has(512) && !var2.has(504)) {
    return true;
            } else if (this.isKnownBlocked(var1, var2)) {
    return true;
            } else {
               if (var1.x == 11920 && var2.y == 6803 && var2.has(131072)) {
    bool var8 = true;
               }

    bool var18 = var1.isCanPathN() && (this.bCanThump || !var1.isThumpN());
    bool var9 = var1.isCanPathW() && (this.bCanThump || !var1.isThumpW());
    bool var10 = var6 && var1.isCollideN() && (var1.x != var2.x || var3 || !var18);
    bool var11 = var17 && var1.isCollideW() && (var1.y != var2.y || var3 || !var9);
               var18 = var2.isCanPathN() && (this.bCanThump || !var2.isThumpN());
               var9 = var2.isCanPathW() && (this.bCanThump || !var2.isThumpW());
    bool var12 = var7 && var2.has(131076) && (var1.x != var2.x || var3 || !var18);
    bool var13 = var5 && var2.has(131074) && (var1.y != var2.y || var3 || !var9);
               if (!var10 && !var11 && !var12 && !var13) {
    bool var14 = var2.x != var1.x && var2.y != var1.y;
                  if (var14) {
    Square var15 = PolygonalMap2.instance.getSquare(var1.x, var2.y, var1.z);
    Square var16 = PolygonalMap2.instance.getSquare(var2.x, var1.y, var1.z);
                     if (!$assertionsDisabled && (var15 == var1 || var15 == var2)) {
                        throw std::make_unique<AssertionError>();
                     }

                     if (!$assertionsDisabled && (var16 == var1 || var16 == var2)) {
                        throw std::make_unique<AssertionError>();
                     }

                     if (var2.x == var1.x + 1 && var2.y == var1.y + 1 && var15 != nullptr && var16 != nullptr) {
                        if (var15.has(4096) && var16.has(2048)) {
    return true;
                        }

                        if (var15.isThumpN() && var16.isThumpW()) {
    return true;
                        }
                     }

                     if (var2.x == var1.x - 1 && var2.y == var1.y - 1 && var15 != nullptr && var16 != nullptr) {
                        if (var15.has(2048) && var16.has(4096)) {
    return true;
                        }

                        if (var15.isThumpW() && var16.isThumpN()) {
    return true;
                        }
                     }

                     if (var15 != nullptr && this.canNotMoveBetween(var1, var15, true)) {
    return true;
                     }

                     if (var16 != nullptr && this.canNotMoveBetween(var1, var16, true)) {
    return true;
                     }

                     if (var15 != nullptr && this.canNotMoveBetween(var2, var15, true)) {
    return true;
                     }

                     if (var16 != nullptr && this.canNotMoveBetween(var2, var16, true)) {
    return true;
                     }
                  }

    return false;
               } else {
    return true;
               }
            }
         } else {
    return true;
         }
      }
   }

    bool isKnownBlocked(Square var1, Square var2) {
      if (var1.z != var2.z) {
    return false;
      } else {
    KnownBlockedEdges var3 = (KnownBlockedEdges)this.knownBlockedEdges.get(var1.ID);
    KnownBlockedEdges var4 = (KnownBlockedEdges)this.knownBlockedEdges.get(var2.ID);
         return var3 != nullptr && var3.isBlocked(var2.x, var2.y) ? true : var4 != nullptr && var4.isBlocked(var1.x, var1.y);
      }
   }
}
} // namespace vehicles
} // namespace zombie
