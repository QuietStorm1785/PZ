#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMapLong/IteratorLong.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
   NonBlockingHashMapLong$2(NonBlockingHashMapLong var1) {
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

   public NonBlockingHashMapLong<TypeV>.IteratorLong iterator() {
      return std::make_shared<IteratorLong>(this.this$0);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
