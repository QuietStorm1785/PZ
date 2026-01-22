#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ASearchNode.h"
#include "astar/ISearchNode.h"

namespace astar {
namespace tests {


class SearchNode2D : public ASearchNode {
public:
    int x;
    int y;
    SearchNode2D parent;
    GoalNode2D goal;

    public SearchNode2D(int var1, int var2, SearchNode2D var3, GoalNode2D var4) {
      this.x = var1;
      this.y = var2;
      this.parent = var3;
      this.goal = var4;
   }

    SearchNode2D getParent() {
      return this.parent;
   }

   public std::vector<ISearchNode> getSuccessors() {
    std::vector var1 = new std::vector();
      var1.push_back(std::make_shared<SearchNode2D>(this.x - 1, this.y, this, this.goal));
      var1.push_back(std::make_shared<SearchNode2D>(this.x + 1, this.y, this, this.goal));
      var1.push_back(std::make_shared<SearchNode2D>(this.x, this.y + 1, this, this.goal));
      var1.push_back(std::make_shared<SearchNode2D>(this.x, this.y - 1, this, this.goal));
    return var1;
   }

    double h() {
      return this.dist(this.goal.getX(), this.goal.getY());
   }

    double c(ISearchNode var1) {
    SearchNode2D var2 = this.castToSearchNode2D(var1);
      return 1.0;
   }

    void getSuccessors(std::vector<ISearchNode> var1) {
      var1.push_back(std::make_shared<SearchNode2D>(this.x - 1, this.y, this, this.goal));
      var1.push_back(std::make_shared<SearchNode2D>(this.x + 1, this.y, this, this.goal));
      var1.push_back(std::make_shared<SearchNode2D>(this.x, this.y + 1, this, this.goal));
      var1.push_back(std::make_shared<SearchNode2D>(this.x, this.y - 1, this, this.goal));
   }

    void setParent(ISearchNode var1) {
      this.parent = this.castToSearchNode2D(var1);
   }

    bool equals(void* var1) {
      return !(dynamic_cast<SearchNode2D*>(var1) != nullptr var2) ? false : this.x == var2.getX() && this.y == var2.getY();
   }

    int hashCode() {
      return 41 * (41 + this.x + this.y);
   }

    double dist(int var1, int var2) {
      return Math.sqrt(Math.pow(this.x - var1, 2.0) + Math.pow(this.y - var2, 2.0));
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    std::string toString() {
      return "(" + int.toString(this.x) + ";" + int.toString(this.y) + ";h:" + double.toString(this.h()) + ";g:" + double.toString(this.g()) + ")";
   }

    SearchNode2D castToSearchNode2D(ISearchNode var1) {
      return (SearchNode2D)var1;
   }

    int keyCode() {
    return nullptr;
   }
}
} // namespace tests
} // namespace astar
