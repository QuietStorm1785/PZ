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


class Maps {
public:
   Maps$6(Iterator var1) {
      this.val$entryIterator = var1;
   }

    bool hasNext() {
      return this.val$entryIterator.hasNext();
   }

   public Entry<K, V> next() {
      return Maps.unmodifiableEntry((Entry)this.val$entryIterator.next());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
