#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapEntrySet {
public:
   private const transient ImmutableMap<K, V> map;
   private const transient Entry<K, V>[] entries;

   ImmutableMapEntrySet$RegularEntrySet(ImmutableMap<K, V> map, Entry<K, V>[] entries) {
      this.map = map;
      this.entries = entries;
   }

   ImmutableMap<K, V> map() {
      return this.map;
   }

   public UnmodifiableIterator<Entry<K, V>> iterator() {
      return Iterators.forArray(this.entries);
   }

   ImmutableList<Entry<K, V>> createAsList() {
      return std::make_shared<RegularImmutableAsList>(this, this.entries);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
