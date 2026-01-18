#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClosedSetHash {
public:
 private TIntObjectHashMap<ISearchNode> hashMap = std::make_unique<TIntObjectHashMap<>>();
 private Comparator<ISearchNode> comp;
 private static ClosedSetHash.MinNodeProc minNodeProc = new ClosedSetHash.MinNodeProc();

 public ClosedSetHash(Comparator<ISearchNode> comparator) {
 this->comp = comparator;
 }

 bool contains(ISearchNode iSearchNode) {
 return this->hashMap.containsKey(iSearchNode.keyCode());
 }

 void add(ISearchNode iSearchNode) {
 this->hashMap.put(iSearchNode.keyCode(), iSearchNode);
 }

 ISearchNode min() {
 minNodeProc.comp = this->comp;
 minNodeProc.candidate = nullptr;
 this->hashMap.forEachValue(minNodeProc);
 return minNodeProc.candidate;
 }

 void clear() {
 this->hashMap.clear();
 }

 private static class MinNodeProc implements TObjectProcedure<ISearchNode> {
 Comparator<ISearchNode> comp;
 ISearchNode candidate;

 bool execute(ISearchNode iSearchNode) {
 if (this->candidate.empty()) {
 this->candidate = iSearchNode;
 return true;
 } else {
 if (this->comp.compare(iSearchNode, this->candidate) < 0) {
 this->candidate = iSearchNode;
 }

 return true;
 }
 }
 }
}
} // namespace datastructures
} // namespace astar
