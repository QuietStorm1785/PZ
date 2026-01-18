#pragma once
#include "astar/IGoalNode.h"
#include "astar/ISearchNode.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
namespace tests {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GoalNode2D {
public:
  int x;
  int y;

public
  GoalNode2D(int int0, int int1) {
    this.x = int0;
    this.y = int1;
  }

  bool inGoal(ISearchNode iSearchNode) {
    return !(iSearchNode instanceof SearchNode2D searchNode2D)
               ? false
               : this.x == searchNode2D.getX() && this.y == searchNode2D.getY();
  }

  int getX() { return this.x; }

  int getY() { return this.y; }
}
} // namespace tests
} // namespace astar
