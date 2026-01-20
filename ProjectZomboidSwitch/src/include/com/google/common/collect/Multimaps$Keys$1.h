#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/Keys.h"
#include "com/google/common/collect/Multimaps/Keys/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$Keys$1(Keys var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

   com.google.common.collect.Multiset.Entry<K> transform(Entry<K, Collection<V>> backingEntry) {
      return std::make_shared<1>(this, backingEntry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
