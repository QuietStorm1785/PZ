#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedEntries.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$ConstrainedEntries$1(ConstrainedEntries var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

   Entry<K, V> transform(Entry<K, V> from) {
      return MapConstraints.access$500(from, this.this$0.constraint);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
