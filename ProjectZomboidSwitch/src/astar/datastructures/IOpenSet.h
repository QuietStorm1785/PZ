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

class IOpenSet {
public:
 virtual ~IOpenSet() = default;
 void add(ISearchNode var1);

 void remove(ISearchNode var1);

 ISearchNode poll();

 ISearchNode getNode(ISearchNode var1);

 int size();

 void clear();
}
} // namespace datastructures
} // namespace astar
