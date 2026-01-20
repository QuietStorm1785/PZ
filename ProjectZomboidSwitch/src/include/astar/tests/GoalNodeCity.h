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


class GoalNodeCity {
public:
    std::string name;

    public GoalNodeCity(const std::string& var1) {
      this.name = var1;
   }

    bool inGoal(ISearchNode var1) {
      return dynamic_cast<SearchNodeCity*>(var1) != nullptr var2 ? this.name == var2.getName() : false;
   }
}
} // namespace tests
} // namespace astar
