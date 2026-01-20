#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Multimaps/UnmodifiableMultimap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$UnmodifiableMultimap$1(UnmodifiableMultimap var1) {
      this.this$0 = var1;
   }

   public Collection<V> apply(Collection<V> collection) {
      return Multimaps.access$000(collection);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
