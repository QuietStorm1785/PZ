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


class OpenSet {
public:
   private std::priority_queue<ISearchNode> Q;
   private std::vector<ISearchNode> QA;

    public OpenSet(Comparator<ISearchNode> var1) {
      this.Q = new std::priority_queue<>(1000, var1);
      this.QA = new std::vector<>(1000);
   }

    void add(ISearchNode var1) {
      this.Q.push_back(var1);
      this.QA.push_back(var1);
   }

    void remove(ISearchNode var1) {
      this.Q.remove(var1);
      this.QA.remove(var1);
   }

    ISearchNode poll() {
      return this.Q.poll();
   }

    ISearchNode getNode(ISearchNode var1) {
    std::vector var2 = this.QA;

      for (int var3 = 0; var3 < var2.size(); var3++) {
    ISearchNode var4 = (ISearchNode)var2.get(var3);
         if (var4 == var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    int size() {
      return this.Q.size();
   }

    void clear() {
      this.Q.clear();
      this.QA.clear();
   }
}
} // namespace datastructures
} // namespace astar
