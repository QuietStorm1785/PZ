#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/THashSet.h"

namespace zombie {
namespace util {


class Pool {
public:
   const THashSet<IPooledObject> inUse = std::make_unique<THashSet>();
   const List<IPooledObject> released = std::make_unique<std::vector<>>();

   Pool$PoolStacks() {
      this.inUse.setAutoCompactionFactor(0.0F);
   }
}
} // namespace util
} // namespace zombie
