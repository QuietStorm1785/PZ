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


class MapConstraints {
public:
   MapConstraints$1(Entry var1, MapConstraint var2) {
      this.val$entry = var1;
      this.val$constraint = var2;
   }

   protected Entry<K, V> delegate() {
      return this.val$entry;
   }

    V setValue(V value) {
      this.val$constraint.checkKeyValue(this.getKey(), value);
      return (V)this.val$entry.setValue(value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
