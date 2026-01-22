#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/IGoalNode.h"
#include "astar/ISearchNode.h"
#include "zombie/vehicles/PolygonalMap2/SearchNode.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    SearchNode searchNode;

   private PolygonalMap2$GoalNode() {
   }

   PolygonalMap2$GoalNode init(SearchNode var1) {
      this.searchNode = var1;
    return this;
   }

    bool inGoal(ISearchNode var1) {
      if (this.searchNode.tx != -1) {
    SearchNode var2 = (SearchNode)var1;
    int var3 = (int)var2.getX();
    int var4 = (int)var2.getY();
         if (var3 % 10 == 0 && PolygonalMap2.instance.getChunkFromSquarePos(var3 - 1, var4) == nullptr) {
    return true;
         } else if (var3 % 10 == 9 && PolygonalMap2.instance.getChunkFromSquarePos(var3 + 1, var4) == nullptr) {
    return true;
         } else {
            return var4 % 10 == 0 && PolygonalMap2.instance.getChunkFromSquarePos(var3, var4 - 1) == nullptr
               ? true
               : var4 % 10 == 9 && PolygonalMap2.instance.getChunkFromSquarePos(var3, var4 + 1) == nullptr;
         }
      } else {
    return var1 = = this.searchNode;
      }
   }
}
} // namespace vehicles
} // namespace zombie
