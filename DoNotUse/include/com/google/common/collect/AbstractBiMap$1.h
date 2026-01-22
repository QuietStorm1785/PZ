#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractBiMap/BiMapEntry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractBiMap {
public:
   Entry<K, V> entry;

   AbstractBiMap$1(AbstractBiMap var1, Iterator var2) {
      this.this$0 = var1;
      this.val$iterator = var2;
   }

    bool hasNext() {
      return this.val$iterator.hasNext();
   }

   public Entry<K, V> next() {
      this.entry = (Entry<K, V>)this.val$iterator.next();
      return std::make_shared<BiMapEntry>(this.this$0, this.entry);
   }

    void remove() {
      CollectPreconditions.checkRemove(this.entry != nullptr);
    V value = (V)this.entry.getValue();
      this.val$iterator.remove();
      AbstractBiMap.access$600(this.this$0, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
