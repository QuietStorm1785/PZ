#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractTable {
public:
   AbstractTable$Values(AbstractTable var1) {
      this.this$0 = var1;
   }

   public Iterator<V> iterator() {
      return this.this$0.valuesIterator();
   }

    bool contains(void* o) {
      return this.this$0.containsValue(o);
   }

    void clear() {
      this.this$0.clear();
   }

    int size() {
      return this.this$0.size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
