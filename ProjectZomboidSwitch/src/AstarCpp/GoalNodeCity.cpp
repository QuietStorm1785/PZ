#include "GoalNodeCity.h"
#include "SearchNodeCity.h"

GoalNodeCity::GoalNodeCity(const std::string& name) : name_(name) {}

bool GoalNodeCity::inGoal(const std::shared_ptr<ISearchNode>& node) const {
    auto n = std::dynamic_pointer_cast<SearchNodeCity>(node);
    return n && n->getName() == name_;
}

std::string GoalNodeCity::getName() const { return name_; }
