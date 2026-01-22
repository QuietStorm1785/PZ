#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMapValues.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   Synchronized$SynchronizedAsMapValues$1(SynchronizedAsMapValues var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

   Collection<V> transform(Collection<V> from) {
      return Synchronized.access$400(from, this.this$0.mutex);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
