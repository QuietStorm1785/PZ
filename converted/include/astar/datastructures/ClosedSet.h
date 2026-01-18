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


class ClosedSet {
public:
 private ArrayList<ISearchNode> list = std::make_unique<ArrayList<>>();
 private Comparator<ISearchNode> comp;

 public ClosedSet(Comparator<ISearchNode> comparator) {
 this->comp = comparator;
 }

 bool contains(ISearchNode iSearchNode) {
 return this->list.contains(iSearchNode);
 }

 void add(ISearchNode iSearchNode) {
 this->list.add(iSearchNode);
 }

 ISearchNode min() {
 return Collections.min(this->list, this->comp);
 }

 void clear() {
 this->list.clear();
 }
}
} // namespace datastructures
} // namespace astar
