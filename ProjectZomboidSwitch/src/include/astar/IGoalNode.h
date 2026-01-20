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
    virtual bool inGoal(const std::shared_ptr<ISearchNode>& node) const = 0;
};
} // namespace astar
