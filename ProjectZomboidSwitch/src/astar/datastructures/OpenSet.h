#pragma once
#include "astar/ISearchNode.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class OpenSet {
public:
private
 PriorityQueue<ISearchNode> Q;
private
 ArrayList<ISearchNode> QA;

public
 OpenSet(Comparator<ISearchNode> comparator) {
 this->Q = new PriorityQueue<>(1000, comparator);
 this->QA = new ArrayList<>(1000);
 }

 void add(ISearchNode iSearchNode) {
 this->Q.add(iSearchNode);
 this->QA.add(iSearchNode);
 }

 void remove(ISearchNode iSearchNode) {
 this->Q.remove(iSearchNode);
 this->QA.remove(iSearchNode);
 }

 ISearchNode poll() { return this->Q.poll(); }

 ISearchNode getNode(ISearchNode iSearchNode1) {
 std::vector arrayList = this->QA;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 ISearchNode iSearchNode0 = (ISearchNode)arrayList.get(int0);
 if (iSearchNode0 == iSearchNode1) {
 return iSearchNode0;
 }
 }

 return nullptr;
 }

 int size() { return this->Q.size(); }

 void clear() {
 this->Q.clear();
 this->QA.clear();
 }
}
} // namespace datastructures
} // namespace astar
