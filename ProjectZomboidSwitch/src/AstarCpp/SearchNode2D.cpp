#include "SearchNode2D.h"
#include "GoalNode2D.h"
#include <cmath>

SearchNode2D::SearchNode2D(int x, int y, std::shared_ptr<SearchNode2D> parent, std::shared_ptr<GoalNode2D> goal)
    : x_(x), y_(y), parent_(parent), goal_(goal) {}

std::shared_ptr<ISearchNode> SearchNode2D::getParent() const {
    return parent_;
}

void SearchNode2D::getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const {
    outSuccessors.push_back(std::make_shared<SearchNode2D>(x_ - 1, y_, std::make_shared<SearchNode2D>(*this), goal_));
    outSuccessors.push_back(std::make_shared<SearchNode2D>(x_ + 1, y_, std::make_shared<SearchNode2D>(*this), goal_));
    outSuccessors.push_back(std::make_shared<SearchNode2D>(x_, y_ + 1, std::make_shared<SearchNode2D>(*this), goal_));
    outSuccessors.push_back(std::make_shared<SearchNode2D>(x_, y_ - 1, std::make_shared<SearchNode2D>(*this), goal_));
}

double SearchNode2D::h() const {
    return std::abs(goal_->getX() - x_) + std::abs(goal_->getY() - y_);
}

double SearchNode2D::c(const std::shared_ptr<ISearchNode>& other) const {
    return 1.0;
}

int SearchNode2D::keyCode() const {
    return x_ * 10000 + y_;
}

bool SearchNode2D::equals(const std::shared_ptr<ISearchNode>& other) const {
    auto o = std::dynamic_pointer_cast<SearchNode2D>(other);
    return o && o->x_ == x_ && o->y_ == y_;
}

int SearchNode2D::hashCode() const {
    return keyCode();
}

int SearchNode2D::getX() const { return x_; }
int SearchNode2D::getY() const { return y_; }
