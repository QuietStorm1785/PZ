#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/Entries.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMultimap {
public:
   private AbstractMultimap$Entries(AbstractMultimap var1) {
      this.this$0 = var1;
   }

   Multimap<K, V> multimap() {
      return this.this$0;
   }

   public Iterator<Entry<K, V>> iterator() {
      return this.this$0.entryIterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
