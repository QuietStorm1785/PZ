#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMapLong/SnapshotV.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
   NonBlockingHashMapLong$1(NonBlockingHashMapLong var1) {
      this.this$0 = var1;
   }

    void clear() {
      this.this$0.clear();
   }

    int size() {
      return this.this$0.size();
   }

    bool contains(void* var1) {
      return this.this$0.containsValue(var1);
   }

   public Iterator<TypeV> iterator() {
      return std::make_shared<SnapshotV>(this.this$0);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
