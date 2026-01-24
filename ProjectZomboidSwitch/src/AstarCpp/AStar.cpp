#include "AstarCpp/AStar.h"
#include <queue>
#include <unordered_set>

std::shared_ptr<ISearchNode> AStar::search(const std::shared_ptr<ISearchNode>& start,
                                           const std::shared_ptr<IGoalNode>& goal,
                                           int maxSteps) {
    struct NodeCmp {
        bool operator()(const std::shared_ptr<ISearchNode>& a, const std::shared_ptr<ISearchNode>& b) const {
            return a->f() > b->f();
        }
    };
    std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp> openSet;
    std::unordered_set<int> closedSet;
    int steps = 0;

    start->setDepth(0);
    openSet.push(start);

    while (!openSet.empty() && (maxSteps < 0 || steps < maxSteps)) {
        auto current = openSet.top();
        openSet.pop();
        ++steps;

        if (goal->inGoal(current)) {
            return current;
        }
        closedSet.insert(current->keyCode());

        std::vector<std::shared_ptr<ISearchNode>> successors;
        current->getSuccessors(successors);
        for (auto& succ : successors) {
            if (closedSet.count(succ->keyCode())) continue;
            succ->setParent(current);
            succ->setDepth(current->getDepth() + 1);
            openSet.push(succ);
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<ISearchNode>> AStar::shortestPath(const std::shared_ptr<ISearchNode>& start,
                                                              const std::shared_ptr<IGoalNode>& goal,
                                                              int maxSteps) {
    auto finalNode = search(start, goal, maxSteps);
    std::vector<std::shared_ptr<ISearchNode>> path;
    if (!finalNode) return path;
    for (auto node = finalNode; node; node = node->getParent()) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
