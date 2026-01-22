#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/UnmodifiableEntries.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$UnmodifiableEntrySet(Set<Entry<K, V>> entries) {
      super(entries);
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
