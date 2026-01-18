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
