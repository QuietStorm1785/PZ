#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/EntryIterator.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$EntrySet(ConcurrentMap<?, ?> var1, ConcurrentMap map) {
      super(var1, map);
      this.this$0 = var1;
   }

   public Iterator<Entry<K, V>> iterator() {
      return std::make_shared<EntryIterator>(this.this$0);
   }

    bool contains(void* o) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> e = (Entry<?, ?>)o;
    void* key = e.getKey();
         if (key == nullptr) {
    return false;
         } else {
    V v = (V)this.this$0.get(key);
            return v != nullptr && this.this$0.valueEquivalence.equivalent(e.getValue(), v);
         }
      }
   }

    bool remove(void* o) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> e = (Entry<?, ?>)o;
    void* key = e.getKey();
         return key != nullptr && this.this$0.remove(key, e.getValue());
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
