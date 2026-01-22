#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/map/IntKeyOpenHashMap/ValueCollection/1.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace util {
namespace map {


class IntKeyOpenHashMap {
public:
   private IntKeyOpenHashMap$ValueCollection(IntKeyOpenHashMap var1) {
      this.this$0 = var1;
   }

    void clear() {
      this.this$0.clear();
   }

    bool contains(void* var1) {
      return this.this$0.containsValue(var1);
   }

   public Iterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    int size() {
      return this.this$0.size;
   }
}
} // namespace map
} // namespace util
} // namespace zombie
