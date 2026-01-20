#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMultimap {
public:
   AbstractMultimap$Values(AbstractMultimap var1) {
      this.this$0 = var1;
   }

   public Iterator<V> iterator() {
      return this.this$0.valueIterator();
   }

    int size() {
      return this.this$0.size();
   }

    bool contains(@Nullable Object) {
      return this.this$0.containsValue(o);
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
