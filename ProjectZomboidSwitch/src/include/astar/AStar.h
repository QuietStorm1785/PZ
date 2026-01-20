#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/AStar$SearchNodeComparator.h"
#include "astar/datastructures/ClosedSet.h"
#include "astar/datastructures/ClosedSetHash.h"
#include "astar/datastructures/IClosedSet.h"
#include "astar/datastructures/IOpenSet.h"
#include "astar/datastructures/OpenSet.h"

namespace astar {


class AStar {
public:
    AStar()
        : verbose(0), maxSteps(-1), numSearchSteps(0) {}

    std::vector<std::shared_ptr<ISearchNode>> shortestPath(const std::shared_ptr<ISearchNode>& start, const std::shared_ptr<IGoalNode>& goal) {
        auto result = search(start, goal);
        return result ? path(result) : std::vector<std::shared_ptr<ISearchNode>>{};
    }

    std::shared_ptr<ISearchNode> search(const std::shared_ptr<ISearchNode>& start, const std::shared_ptr<IGoalNode>& goal);

    static std::vector<std::shared_ptr<ISearchNode>> path(const std::shared_ptr<ISearchNode>& node) {
        std::vector<std::shared_ptr<ISearchNode>> result;
        auto current = node;
        while (current) {
            result.insert(result.begin(), current);
            current = current->getParent();
        }
        return result;
    }

    int numSearchSteps() const { return numSearchSteps; }
    std::shared_ptr<ISearchNode> bestNodeAfterSearch() const { return bestNodeAfterSearch_; }
    void setMaxSteps(int steps) { maxSteps = steps; }

    int verbose;
    int maxSteps;
    int numSearchSteps;
    std::shared_ptr<ISearchNode> bestNodeAfterSearch_;
    std::vector<std::shared_ptr<ISearchNode>> successorNodes;
    std::shared_ptr<IOpenSet> openSet;
    std::shared_ptr<IClosedSet> closedSetHash;
    std::shared_ptr<IClosedSet> closedSetNoHash;
};
} // namespace astar
