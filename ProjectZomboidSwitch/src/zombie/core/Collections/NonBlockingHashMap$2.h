#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMap/SnapshotK.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMap {
public:
   NonBlockingHashMap$2(NonBlockingHashMap var1) {
      this.this$0 = var1;
   }

    void clear() {
      this.this$0.clear();
   }

    int size() {
      return this.this$0.size();
   }

    bool contains(void* var1) {
      return this.this$0.containsKey(var1);
   }

    bool remove(void* var1) {
      return this.this$0.remove(var1) != nullptr;
   }

   public Iterator<TypeK> iterator() {
      return std::make_shared<SnapshotK>(this.this$0);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
