#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>

namespace astar {
namespace datastructures {


class ClosedSetHash {
public:
   Comparator<ISearchNode> comp;
    ISearchNode candidate;

   private ClosedSetHash$MinNodeProc() {
   }

    bool execute(ISearchNode var1) {
      if (this.candidate == nullptr) {
         this.candidate = var1;
    return true;
      } else {
         if (this.comp.compare(var1, this.candidate) < 0) {
            this.candidate = var1;
         }

    return true;
      }
   }
}
} // namespace datastructures
} // namespace astar
