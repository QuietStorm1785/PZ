#ifndef ASTARCPP_IGOALNODE_H
#define ASTARCPP_IGOALNODE_H

#include <memory>
#include "ISearchNode.h"

class IGoalNode {
public:
    virtual ~IGoalNode() = default;
    virtual bool inGoal(const std::shared_ptr<ISearchNode>& node) const = 0;
};

#endif // ASTARCPP_IGOALNODE_H
