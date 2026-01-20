#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMapEntries.h"
#include "com/google/common/collect/Synchronized/SynchronizedAsMapEntries/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   Synchronized$SynchronizedAsMapEntries$1(SynchronizedAsMapEntries var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

   Entry<K, Collection<V>> transform(Entry<K, Collection<V>> entry) {
      return std::make_shared<1>(this, entry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
