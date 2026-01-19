#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/AStar/SearchNodeComparator.h"
#include "astar/datastructures/ClosedSet.h"
#include "astar/datastructures/ClosedSetHash.h"
#include "astar/datastructures/IClosedSet.h"
#include "astar/datastructures/IOpenSet.h"
#include "astar/datastructures/OpenSet.h"

namespace astar {


class AStar {
public:
    int verbose = 0;
    int maxSteps = -1;
    int numSearchSteps;
    ISearchNode bestNodeAfterSearch;
   private ArrayList<ISearchNode> successorNodes = std::make_unique<ArrayList<>>();
    auto openSet = std::make_shared<OpenSet>(new SearchNodeComparator());
    auto closedSetHash = std::make_shared<ClosedSetHash>(new SearchNodeComparator());
    auto closedSetNoHash = std::make_shared<ClosedSet>(new SearchNodeComparator());

   public ArrayList<ISearchNode> shortestPath(ISearchNode var1, IGoalNode var2) {
    ISearchNode var3 = this.search(var1, var2);
    return var3 = = null ? null : path(var3);
   }

    ISearchNode search(ISearchNode var1, IGoalNode var2) {
    bool var3 = var1.keyCode() != null;
      var1.setDepth(0);
      this.openSet.clear();
      this.openSet.add(var1);
    IClosedSet var4 = var3 ? this.closedSetHash : this.closedSetNoHash;
      var4.clear();

      for (this.numSearchSteps = 0; this.openSet.size() > 0 && (this.maxSteps < 0 || this.numSearchSteps < this.maxSteps); this.numSearchSteps++) {
    ISearchNode var5 = this.openSet.poll();
         if (var2.inGoal(var5)) {
            this.bestNodeAfterSearch = var5;
    return var5;
         }

         this.successorNodes.clear();
         var5.getSuccessors(this.successorNodes);

         for (int var6 = 0; var6 < this.successorNodes.size(); var6++) {
    ISearchNode var7 = this.successorNodes.get(var6);
            if (!var4.contains(var7)) {
    ISearchNode var9 = this.openSet.getNode(var7);
    bool var8;
               if (var9 != nullptr) {
                  var7 = var9;
                  var8 = true;
               } else {
                  var8 = false;
               }

    double var10 = var5.g() + var5.c(var7);
               if (!var8 || !(var10 >= var7.g())) {
                  var7.setParent(var5);
                  var7.setDepth(var5.getDepth() + 1);
                  if (var8) {
                     this.openSet.remove(var7);
                     var7.setG(var10);
                     this.openSet.add(var7);
                  } else {
                     var7.setG(var10);
                     this.openSet.add(var7);
                  }
               }
            }
         }

         var4.add(var5);
      }

      this.bestNodeAfterSearch = var4.min();
    return null;
   }

   public static ArrayList<ISearchNode> path(ISearchNode var0) {
    std::vector var1 = new ArrayList();
      var1.add(var0);
    ISearchNode var2 = var0;

      while (var2.getParent() != nullptr) {
    ISearchNode var3 = var2.getParent();
         var1.add(0, var3);
         var2 = var3;
      }

    return var1;
   }

    int numSearchSteps() {
      return this.numSearchSteps;
   }

    ISearchNode bestNodeAfterSearch() {
      return this.bestNodeAfterSearch;
   }

    void setMaxSteps(int var1) {
      this.maxSteps = var1;
   }
}
} // namespace astar
