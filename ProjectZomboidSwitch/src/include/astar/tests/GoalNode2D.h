#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/IGoalNode.h"
#include "astar/ISearchNode.h"

namespace astar {
namespace tests {


class GoalNode2D {
public:
    int x;
    int y;

    public GoalNode2D(int var1, int var2) {
      this.x = var1;
      this.y = var2;
   }

    bool inGoal(ISearchNode var1) {
      return !(dynamic_cast<SearchNode2D*>(var1) != nullptr var2) ? false : this.x == var2.getX() && this.y == var2.getY();
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }
}
} // namespace tests
} // namespace astar
