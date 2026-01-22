#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace astar {


class AStarSearchNodeComparator {
public:
   int operator()(const std::shared_ptr<ISearchNode>& lhs, const std::shared_ptr<ISearchNode>& rhs) const {
      if (!lhs || !rhs) return 0;
      double lf = lhs->f();
      double rf = rhs->f();
      if (lf < rf) return -1;
      if (lf > rf) return 1;
      return 0;
   }
};
} // namespace astar
