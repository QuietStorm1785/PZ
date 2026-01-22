#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidHashMap {
public:
   private ZomboidHashMap$Values(ZomboidHashMap var1) {
      this.this$0 = var1;
   }

   public Iterator<V> iterator() {
      return this.this$0.newValueIterator();
   }

    int size() {
      return this.this$0.size;
   }

    bool contains(void* var1) {
      return this.this$0.containsValue(var1);
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
