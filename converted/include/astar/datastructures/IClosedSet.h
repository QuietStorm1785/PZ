#pragma once
#include "astar/ISearchNode.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IClosedSet {
public:
  virtual ~IClosedSet() = default;
  bool contains(ISearchNode var1);

  void add(ISearchNode var1);

  ISearchNode min();

  void clear();
}
} // namespace datastructures
} // namespace astar
