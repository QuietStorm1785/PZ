#ifndef ASTARCPP_GOALNODE2D_H
#define ASTARCPP_GOALNODE2D_H

#include "IGoalNode.h"
#include "ISearchNode.h"
#include <memory>

class SearchNode2D;

class GoalNode2D : public IGoalNode {
public:
    GoalNode2D(int x, int y);
    bool inGoal(const std::shared_ptr<ISearchNode>& node) const override;
    int getX() const;
    int getY() const;
private:
    int x_;
    int y_;
};

#endif // ASTARCPP_GOALNODE2D_H
