#ifndef ASTARCPP_SEARCHNODE2D_H
#define ASTARCPP_SEARCHNODE2D_H

#include "ASearchNode.h"
#include "IGoalNode.h"
#include <memory>
#include <vector>

class GoalNode2D;

class SearchNode2D : public ASearchNode {
public:
    SearchNode2D(int x, int y, std::shared_ptr<SearchNode2D> parent, std::shared_ptr<GoalNode2D> goal);
    std::shared_ptr<ISearchNode> getParent() const override;
    void getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const override;
    double h() const override;
    double c(const std::shared_ptr<ISearchNode>& other) const override;
    int keyCode() const override;
    bool equals(const std::shared_ptr<ISearchNode>& other) const override;
    int hashCode() const override;
    int getX() const;
    int getY() const;
private:
    int x_;
    int y_;
    std::shared_ptr<SearchNode2D> parent_;
    std::shared_ptr<GoalNode2D> goal_;
};

#endif // ASTARCPP_SEARCHNODE2D_H
