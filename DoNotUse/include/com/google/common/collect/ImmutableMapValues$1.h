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
   const UnmodifiableIterator<Entry<K, V>> entryItr;

   ImmutableMapValues$1(ImmutableMapValues var1) {
      this.this$0 = var1;
      this.entryItr = ImmutableMapValues.access$000(this.this$0).entrySet().iterator();
   }

    bool hasNext() {
      return this.entryItr.hasNext();
   }

    V next() {
      return (V)((Entry)this.entryItr.next()).getValue();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
