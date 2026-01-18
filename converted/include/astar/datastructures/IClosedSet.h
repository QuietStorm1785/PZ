#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
