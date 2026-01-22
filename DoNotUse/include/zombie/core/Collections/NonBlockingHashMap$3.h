#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMap/SnapshotE.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMap {
public:
   NonBlockingHashMap$3(NonBlockingHashMap var1) {
      this.this$0 = var1;
   }

    void clear() {
      this.this$0.clear();
   }

    int size() {
      return this.this$0.size();
   }

    bool remove(void* var1) {
      return !(dynamic_cast<Entry*>(var1) != nullptr var2) ? false : this.this$0.remove(var2.getKey(), var2.getValue());
   }

    bool contains(void* var1) {
      if (!(dynamic_cast<Entry*>(var1) != nullptr var2)) {
    return false;
      } else {
    void* var3 = this.this$0.get(var2.getKey());
         return var3 == var2.getValue());
      }
   }

   public Iterator<Entry<TypeK, TypeV>> iterator() {
      return std::make_shared<SnapshotE>(this.this$0);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
