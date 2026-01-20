#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/EntryIterator.h"
#include "com/google/common/collect/MapMakerInternalMap/SafeToArraySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   MapMakerInternalMap$EntrySet(MapMakerInternalMap var1) {
      super(nullptr);
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
            return v != nullptr && this.this$0.valueEquivalence().equivalent(e.getValue(), v);
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

    int size() {
      return this.this$0.size();
   }

    bool isEmpty() {
      return this.this$0.empty();
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
