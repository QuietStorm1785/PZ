#ifndef ASTARCPP_ASTAR_H
#define ASTARCPP_ASTAR_H

#include "ISearchNode.h"
#include "IGoalNode.h"
#include <memory>
#include <vector>

class AStar {
public:
    // Returns the final node if found, nullptr otherwise
    std::shared_ptr<ISearchNode> search(const std::shared_ptr<ISearchNode>& start,
                                        const std::shared_ptr<IGoalNode>& goal,
                                        int maxSteps = -1);
    // Returns the path from start to goal as a vector of nodes
    std::vector<std::shared_ptr<ISearchNode>> shortestPath(const std::shared_ptr<ISearchNode>& start,
                                                           const std::shared_ptr<IGoalNode>& goal,
                                                           int maxSteps = -1);
};

#endif // ASTARCPP_ASTAR_H
