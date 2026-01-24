#ifndef ASTARCPP_GOALNODECITY_H
#define ASTARCPP_GOALNODECITY_H

#include "IGoalNode.h"
#include "ISearchNode.h"
#include <string>
#include <memory>

class SearchNodeCity;

class GoalNodeCity : public IGoalNode {
public:
    GoalNodeCity(const std::string& name);
    bool inGoal(const std::shared_ptr<ISearchNode>& node) const override;
    std::string getName() const;
private:
    std::string name_;
};

#endif // ASTARCPP_GOALNODECITY_H
