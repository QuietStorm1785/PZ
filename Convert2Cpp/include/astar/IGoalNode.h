#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace astar {

class IGoalNode {
public:
    virtual ~IGoalNode() = default;
    bool inGoal(ISearchNode var1);
}
} // namespace astar
