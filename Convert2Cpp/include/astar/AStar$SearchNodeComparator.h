#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace astar {


class AStar {
public:
    int compare(ISearchNode var1, ISearchNode var2) {
      return Double.compare(var1.f(), var2.f());
   }
}
} // namespace astar
