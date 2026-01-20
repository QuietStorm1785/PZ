#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedEntries.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$ConstrainedEntrySet(Set<Entry<K, V>> entries, MapConstraint<? super K, ? super V> constraint) {
      super(entries, constraint);
   }

    bool equals(@Nullable Object) {
      return Sets.equalsImpl(this, object);
   }

    int hashCode() {
      return Sets.hashCodeImpl(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
