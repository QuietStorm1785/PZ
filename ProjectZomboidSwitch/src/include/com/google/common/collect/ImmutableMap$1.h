#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   ImmutableMap$1(ImmutableMap var1, UnmodifiableIterator var2) {
      this.this$0 = var1;
      this.val$entryIterator = var2;
   }

    bool hasNext() {
      return this.val$entryIterator.hasNext();
   }

    K next() {
      return (K)((Entry)this.val$entryIterator.next()).getKey();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
