#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMapEntries/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   Synchronized$SynchronizedAsMapEntries$1$1(1 var1, Entry var2) {
      this.this$1 = var1;
      this.val$entry = var2;
   }

   protected Entry<K, Collection<V>> delegate() {
      return this.val$entry;
   }

   public Collection<V> getValue() {
      return Synchronized.access$400((Collection)this.val$entry.getValue(), this.this$1.this$0.mutex);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
