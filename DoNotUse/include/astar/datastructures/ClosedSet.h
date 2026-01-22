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


class ClosedSet {
public:
   private std::vector<ISearchNode> list = std::make_unique<std::vector<>>();
   private Comparator<ISearchNode> comp;

    public ClosedSet(Comparator<ISearchNode> var1) {
      this.comp = var1;
   }

    bool contains(ISearchNode var1) {
      return this.list.contains(var1);
   }

    void add(ISearchNode var1) {
      this.list.push_back(var1);
   }

    ISearchNode min() {
      return Collections.min(this.list, this.comp);
   }

    void clear() {
      this.list.clear();
   }
}
} // namespace datastructures
} // namespace astar
