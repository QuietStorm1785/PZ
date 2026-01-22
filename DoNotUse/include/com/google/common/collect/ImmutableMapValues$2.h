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


class ImmutableMapValues {
public:
   ImmutableMapValues$2(ImmutableMapValues var1, ImmutableList var2) {
      this.this$0 = var1;
      this.val$entryList = var2;
   }

    V get(int index) {
      return (V)((Entry)this.val$entryList.get(index)).getValue();
   }

   ImmutableCollection<V> delegateCollection() {
      return this.this$0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
