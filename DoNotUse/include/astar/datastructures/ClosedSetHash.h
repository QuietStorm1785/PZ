#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"
#include "astar/datastructures/ClosedSetHash/MinNodeProc.h"
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include <algorithm>

namespace astar {
namespace datastructures {


class ClosedSetHash {
public:
   private TIntObjectHashMap<ISearchNode> hashMap = std::make_unique<TIntObjectHashMap>();
   private Comparator<ISearchNode> comp;
    static const MinNodeProc minNodeProc = std::make_shared<MinNodeProc>();

    public ClosedSetHash(Comparator<ISearchNode> var1) {
      this.comp = var1;
   }

    bool contains(ISearchNode var1) {
      return this.hashMap.containsKey(var1.keyCode());
   }

    void add(ISearchNode var1) {
      this.hashMap.put(var1.keyCode(), var1);
   }

    ISearchNode min() {
      minNodeProc.comp = this.comp;
      minNodeProc.candidate = nullptr;
      this.hashMap.forEachValue(minNodeProc);
      return minNodeProc.candidate;
   }

    void clear() {
      this.hashMap.clear();
   }
}
} // namespace datastructures
} // namespace astar
