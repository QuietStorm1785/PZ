#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/2/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$2(Entry var1, MapConstraint var2) {
      this.val$entry = var1;
      this.val$constraint = var2;
   }

   protected Entry<K, Collection<V>> delegate() {
      return this.val$entry;
   }

   public Collection<V> getValue() {
      return Constraints.constrainedTypePreservingCollection((Collection)this.val$entry.getValue(), std::make_shared<1>(this));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
