#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMapEntry/NonTerminalImmutableMapEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapEntry {
public:
   private const transient ImmutableMapEntry<K, V> nextInValueBucket;

   ImmutableMapEntry$NonTerminalImmutableBiMapEntry(K key, V value, ImmutableMapEntry<K, V> nextInKeyBucket, ImmutableMapEntry<K, V> nextInValueBucket) {
      super(key, value, nextInKeyBucket);
      this.nextInValueBucket = nextInValueBucket;
   }

   ImmutableMapEntry<K, V> getNextInValueBucket() {
      return this.nextInValueBucket;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
