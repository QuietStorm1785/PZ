#pragma once
#include "astar/ASearchNode.h"
#include "astar/ISearchNode.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
namespace tests {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SearchNode2D : public ASearchNode {
public:
 int x;
 int y;
 SearchNode2D parent;
 GoalNode2D goal;

public
 SearchNode2D(int int0, int int1, SearchNode2D searchNode2D1,
 GoalNode2D goalNode2D) {
 this->x = int0;
 this->y = int1;
 this->parent = searchNode2D1;
 this->goal = goalNode2D;
 }

 SearchNode2D getParent() { return this->parent; }

public
 ArrayList<ISearchNode> getSuccessors() {
 std::vector arrayList = new ArrayList();
 arrayList.add(new SearchNode2D(this->x - 1, this->y, this, this->goal);
 arrayList.add(new SearchNode2D(this->x + 1, this->y, this, this->goal);
 arrayList.add(new SearchNode2D(this->x, this->y + 1, this, this->goal);
 arrayList.add(new SearchNode2D(this->x, this->y - 1, this, this->goal);
 return arrayList;
 }

 double h() { return this->dist(this->goal.getX(), this->goal.getY()); }

 double c(ISearchNode iSearchNode) {
 SearchNode2D searchNode2D0 = this->castToSearchNode2D(iSearchNode);
 return 1.0;
 }

 void getSuccessors(ArrayList<ISearchNode> arrayList) {
 arrayList.add(new SearchNode2D(this->x - 1, this->y, this, this->goal);
 arrayList.add(new SearchNode2D(this->x + 1, this->y, this, this->goal);
 arrayList.add(new SearchNode2D(this->x, this->y + 1, this, this->goal);
 arrayList.add(new SearchNode2D(this->x, this->y - 1, this, this->goal);
 }

 void setParent(ISearchNode iSearchNode) {
 this->parent = this->castToSearchNode2D(iSearchNode);
 }

 bool equals(void *object) {
 return !(object instanceof SearchNode2D searchNode2D0)
 ? false
 : this->x == searchNode2D0.getX() &&
 this->y == searchNode2D0.getY();
 }

 int hashCode() { return 41 * (41 + this->x + this->y); }

 double dist(int int1, int int0) {
 return Math.sqrt(Math.pow(this->x - int1, 2.0) +
 Math.pow(this->y - int0, 2.0);
 }

 int getX() { return this->x; }

 int getY() { return this->y; }

 std::string toString() {
 return "(" + Integer.toString(this->x) + ";" + Integer.toString(this->y) +
 ";h:" + Double.toString(this->h()) +
 ";g:" + Double.toString(this->g()) + ")";
 }

 SearchNode2D castToSearchNode2D(ISearchNode iSearchNode) {
 return (SearchNode2D)iSearchNode;
 }

 int keyCode() { return nullptr; }
}
} // namespace tests
} // namespace astar
