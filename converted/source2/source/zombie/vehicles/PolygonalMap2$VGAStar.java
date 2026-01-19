package zombie.vehicles;

import astar.AStar;
import astar.ISearchNode;
import gnu.trove.map.hash.TIntObjectHashMap;
import java.util.ArrayList;
import zombie.ai.KnownBlockedEdges;
import zombie.ai.astar.Mover;
import zombie.vehicles.PolygonalMap2.GoalNode;
import zombie.vehicles.PolygonalMap2.Node;
import zombie.vehicles.PolygonalMap2.PathFindRequest;
import zombie.vehicles.PolygonalMap2.SearchNode;
import zombie.vehicles.PolygonalMap2.Square;
import zombie.vehicles.PolygonalMap2.VisibilityGraph;
import zombie.vehicles.PolygonalMap2.VGAStar.InitProc;

final class PolygonalMap2$VGAStar extends AStar {
   ArrayList<VisibilityGraph> graphs;
   final ArrayList<SearchNode> searchNodes = new ArrayList<>();
   final TIntObjectHashMap<SearchNode> nodeMap = new TIntObjectHashMap();
   final GoalNode goalNode = new GoalNode();
   final TIntObjectHashMap<SearchNode> squareToNode = new TIntObjectHashMap();
   Mover mover;
   boolean bCanCrawl;
   boolean bIgnoreCrawlCost;
   boolean bCanThump;
   final TIntObjectHashMap<KnownBlockedEdges> knownBlockedEdges = new TIntObjectHashMap();
   final InitProc initProc = new InitProc(this);

   private PolygonalMap2$VGAStar() {
   }

   PolygonalMap2$VGAStar init(ArrayList<VisibilityGraph> var1, TIntObjectHashMap<Node> var2) {
      this.setMaxSteps(5000);
      this.graphs = var1;
      this.searchNodes.clear();
      this.nodeMap.clear();
      this.squareToNode.clear();
      this.mover = null;
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

      return null;
   }

   boolean isSquareInCluster(Square var1) {
      return this.getVisGraphForSquare(var1) != null;
   }

   SearchNode getSearchNode(Node var1) {
      if (var1.square != null) {
         return this.getSearchNode(var1.square);
      } else {
         SearchNode var2 = (SearchNode)this.nodeMap.get(var1.ID);
         if (var2 == null) {
            var2 = SearchNode.alloc().init(this, var1);
            this.searchNodes.add(var2);
            this.nodeMap.put(var1.ID, var2);
         }

         return var2;
      }
   }

   SearchNode getSearchNode(Square var1) {
      SearchNode var2 = (SearchNode)this.squareToNode.get(var1.ID);
      if (var2 == null) {
         var2 = SearchNode.alloc().init(this, var1);
         this.searchNodes.add(var2);
         this.squareToNode.put(var1.ID, var2);
      }

      return var2;
   }

   SearchNode getSearchNode(int var1, int var2) {
      SearchNode var3 = SearchNode.alloc().init(this, var1, var2);
      this.searchNodes.add(var3);
      return var3;
   }

   ArrayList<ISearchNode> shortestPath(PathFindRequest var1, SearchNode var2, SearchNode var3) {
      this.mover = var1.mover;
      this.bCanCrawl = var1.bCanCrawl;
      this.bIgnoreCrawlCost = var1.bIgnoreCrawlCost;
      this.bCanThump = var1.bCanThump;
      this.goalNode.init(var3);
      return this.shortestPath(var2, this.goalNode);
   }

   boolean canNotMoveBetween(Square var1, Square var2, boolean var3) {
      if (!$assertionsDisabled && Math.abs(var1.x - var2.x) > 1) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && Math.abs(var1.y - var2.y) > 1) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && var1.z != var2.z) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && var1 == var2) {
         throw new AssertionError();
      } else {
         if (var1.x == 10921 && var1.y == 10137 && var2.x == var1.x - 1 && var2.y == var1.y) {
            boolean var4 = true;
         }

         boolean var17 = var2.x < var1.x;
         boolean var5 = var2.x > var1.x;
         boolean var6 = var2.y < var1.y;
         boolean var7 = var2.y > var1.y;
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
                  boolean var8 = true;
               }

               boolean var18 = var1.isCanPathN() && (this.bCanThump || !var1.isThumpN());
               boolean var9 = var1.isCanPathW() && (this.bCanThump || !var1.isThumpW());
               boolean var10 = var6 && var1.isCollideN() && (var1.x != var2.x || var3 || !var18);
               boolean var11 = var17 && var1.isCollideW() && (var1.y != var2.y || var3 || !var9);
               var18 = var2.isCanPathN() && (this.bCanThump || !var2.isThumpN());
               var9 = var2.isCanPathW() && (this.bCanThump || !var2.isThumpW());
               boolean var12 = var7 && var2.has(131076) && (var1.x != var2.x || var3 || !var18);
               boolean var13 = var5 && var2.has(131074) && (var1.y != var2.y || var3 || !var9);
               if (!var10 && !var11 && !var12 && !var13) {
                  boolean var14 = var2.x != var1.x && var2.y != var1.y;
                  if (var14) {
                     Square var15 = PolygonalMap2.instance.getSquare(var1.x, var2.y, var1.z);
                     Square var16 = PolygonalMap2.instance.getSquare(var2.x, var1.y, var1.z);
                     if (!$assertionsDisabled && (var15 == var1 || var15 == var2)) {
                        throw new AssertionError();
                     }

                     if (!$assertionsDisabled && (var16 == var1 || var16 == var2)) {
                        throw new AssertionError();
                     }

                     if (var2.x == var1.x + 1 && var2.y == var1.y + 1 && var15 != null && var16 != null) {
                        if (var15.has(4096) && var16.has(2048)) {
                           return true;
                        }

                        if (var15.isThumpN() && var16.isThumpW()) {
                           return true;
                        }
                     }

                     if (var2.x == var1.x - 1 && var2.y == var1.y - 1 && var15 != null && var16 != null) {
                        if (var15.has(2048) && var16.has(4096)) {
                           return true;
                        }

                        if (var15.isThumpW() && var16.isThumpN()) {
                           return true;
                        }
                     }

                     if (var15 != null && this.canNotMoveBetween(var1, var15, true)) {
                        return true;
                     }

                     if (var16 != null && this.canNotMoveBetween(var1, var16, true)) {
                        return true;
                     }

                     if (var15 != null && this.canNotMoveBetween(var2, var15, true)) {
                        return true;
                     }

                     if (var16 != null && this.canNotMoveBetween(var2, var16, true)) {
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

   boolean isKnownBlocked(Square var1, Square var2) {
      if (var1.z != var2.z) {
         return false;
      } else {
         KnownBlockedEdges var3 = (KnownBlockedEdges)this.knownBlockedEdges.get(var1.ID);
         KnownBlockedEdges var4 = (KnownBlockedEdges)this.knownBlockedEdges.get(var2.ID);
         return var3 != null && var3.isBlocked(var2.x, var2.y) ? true : var4 != null && var4.isBlocked(var1.x, var1.y);
      }
   }
}
