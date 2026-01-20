#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/ValueIterator.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   MapMakerInternalMap$Values(MapMakerInternalMap var1) {
      this.this$0 = var1;
   }

   public Iterator<V> iterator() {
      return std::make_shared<ValueIterator>(this.this$0);
   }

    int size() {
      return this.this$0.size();
   }

    bool isEmpty() {
      return this.this$0.empty();
   }

    bool contains(void* o) {
      return this.this$0.containsValue(o);
   }

    void clear() {
      this.this$0.clear();
   }

   public Object[] toArray() {
      return MapMakerInternalMap.access$800(this).toArray();
   }

   public <E> E[] toArray(E[] a) {
      return MapMakerInternalMap.access$800(this).toArray(a);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
