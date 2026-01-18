#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace astar {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IGoalNode {
public:
 virtual ~IGoalNode() = default;
 bool inGoal(ISearchNode var1);
}
} // namespace astar
