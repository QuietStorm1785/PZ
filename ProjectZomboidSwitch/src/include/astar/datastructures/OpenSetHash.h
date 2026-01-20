#pragma once
#include <map>
#include <queue>
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


class OpenSetHash {
public:
   private HashPriorityQueue<int, ISearchNode> hashQ;
   private Comparator<ISearchNode> comp;

    public OpenSetHash(Comparator<ISearchNode> var1) {
      this.hashQ = std::make_shared<HashPriorityQueue>(var1);
      this.comp = var1;
   }

    void add(ISearchNode var1) {
      this.hashQ.push_back(var1.keyCode(), var1);
   }

    void remove(ISearchNode var1) {
      this.hashQ.remove(var1.keyCode(), var1);
   }

    ISearchNode poll() {
      return (ISearchNode)this.hashQ.poll();
   }

    ISearchNode getNode(ISearchNode var1) {
      return (ISearchNode)this.hashQ.get(var1.keyCode());
   }

    int size() {
      return this.hashQ.size();
   }

    std::string toString() {
      return this.hashQ.getTreeMap().keySet();
   }

    void clear() {
      this.hashQ.clear();
   }
}
} // namespace datastructures
} // namespace astar
