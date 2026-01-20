#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/ZomboidAbstractMap/2/1.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidAbstractMap {
public:
   ZomboidAbstractMap$2(ZomboidAbstractMap var1) {
      this.this$0 = var1;
   }

   public Iterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    int size() {
      return this.this$0.size();
   }

    bool contains(void* var1) {
      return this.this$0.containsValue(var1);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
