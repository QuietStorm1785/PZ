#include "GoalNode2D.h"
#include "SearchNode2D.h"

GoalNode2D::GoalNode2D(int x, int y) : x_(x), y_(y) {}

bool GoalNode2D::inGoal(const std::shared_ptr<ISearchNode>& node) const {
    auto n = std::dynamic_pointer_cast<SearchNode2D>(node);
    return n && n->getX() == x_ && n->getY() == y_;
}

int GoalNode2D::getX() const { return x_; }
int GoalNode2D::getY() const { return y_; }
