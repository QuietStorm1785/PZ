#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedAsMapEntries.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$ConstrainedAsMapEntries$1(ConstrainedAsMapEntries var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

   Entry<K, Collection<V>> transform(Entry<K, Collection<V>> from) {
      return MapConstraints.access$700(from, ConstrainedAsMapEntries.access$600(this.this$0));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
