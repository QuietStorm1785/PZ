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


class ImmutableMultimap {
public:
   ImmutableMultimap$1(ImmutableMultimap var1) {
      super(var1, nullptr);
      this.this$0 = var1;
   }

   Entry<K, V> output(K key, V value) {
      return Maps.immutableEntry(key, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
