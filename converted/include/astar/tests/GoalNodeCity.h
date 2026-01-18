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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GoalNodeCity {
public:
 std::string name;

 public GoalNodeCity(const std::string& string) {
 this->name = string;
 }

 bool inGoal(ISearchNode iSearchNode) {
 return iSearchNode instanceof SearchNodeCity searchNodeCity ? this->name == searchNodeCity.getName() : false;
 }
}
} // namespace tests
} // namespace astar
