#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"
#include <algorithm>

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class OpenSetHash {
public:
 private HashPriorityQueue<Integer, ISearchNode> hashQ;
 private Comparator<ISearchNode> comp;

 public OpenSetHash(Comparator<ISearchNode> comparator) {
 this->hashQ = new HashPriorityQueue<>(comparator);
 this->comp = comparator;
 }

 void add(ISearchNode iSearchNode) {
 this->hashQ.add(iSearchNode.keyCode(), iSearchNode);
 }

 void remove(ISearchNode iSearchNode) {
 this->hashQ.remove(iSearchNode.keyCode(), iSearchNode);
 }

 ISearchNode poll() {
 return this->hashQ.poll();
 }

 ISearchNode getNode(ISearchNode iSearchNode) {
 return this->hashQ.get(iSearchNode.keyCode());
 }

 int size() {
 return this->hashQ.size();
 }

 std::string toString() {
 return this->hashQ.getTreeMap().keySet().toString();
 }

 void clear() {
 this->hashQ.clear();
 }
}
} // namespace datastructures
} // namespace astar
