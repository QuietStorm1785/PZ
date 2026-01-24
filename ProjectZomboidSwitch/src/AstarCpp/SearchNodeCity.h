#ifndef ASTARCPP_SEARCHNODECITY_H
#define ASTARCPP_SEARCHNODECITY_H

#include "ASearchNode.h"
#include <string>
#include <unordered_map>
#include <memory>

class GoalNodeCity;

class SearchNodeCity : public ASearchNode {
public:
    SearchNodeCity(const std::string& name, std::shared_ptr<SearchNodeCity> parent, std::shared_ptr<GoalNodeCity> goal);
    std::shared_ptr<ISearchNode> getParent() const override;
    void getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const override;
    double h() const override;
    double c(const std::shared_ptr<ISearchNode>& other) const override;
    int keyCode() const override;
    bool equals(const std::shared_ptr<ISearchNode>& other) const override;
    int hashCode() const override;
    std::string getName() const;
private:
    std::string name_;
    std::shared_ptr<SearchNodeCity> parent_;
    std::shared_ptr<GoalNodeCity> goal_;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> adjacencyMatrix_;
    void fillAdjacencyMatrix();
};

#endif // ASTARCPP_SEARCHNODECITY_H
