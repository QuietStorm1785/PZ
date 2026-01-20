#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedAsMapValues.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$ConstrainedAsMapValues$1(ConstrainedAsMapValues var1, Iterator var2) {
      this.this$0 = var1;
      this.val$iterator = var2;
   }

    bool hasNext() {
      return this.val$iterator.hasNext();
   }

   public Collection<V> next() {
      return (Collection<V>)((Entry)this.val$iterator.next()).getValue();
   }

    void remove() {
      this.val$iterator.remove();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
