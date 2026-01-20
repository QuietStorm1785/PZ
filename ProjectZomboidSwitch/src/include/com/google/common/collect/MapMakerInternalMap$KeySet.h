#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/KeyIterator.h"
#include "com/google/common/collect/MapMakerInternalMap/SafeToArraySet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   MapMakerInternalMap$KeySet(MapMakerInternalMap var1) {
      super(nullptr);
      this.this$0 = var1;
   }

   public Iterator<K> iterator() {
      return std::make_shared<KeyIterator>(this.this$0);
   }

    int size() {
      return this.this$0.size();
   }

    bool isEmpty() {
      return this.this$0.empty();
   }

    bool contains(void* o) {
      return this.this$0.containsKey(o);
   }

    bool remove(void* o) {
      return this.this$0.remove(o) != nullptr;
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
