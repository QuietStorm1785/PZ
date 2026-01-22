#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapEntry {
public:
   private const transient ImmutableMapEntry<K, V> nextInKeyBucket;

   ImmutableMapEntry$NonTerminalImmutableMapEntry(K key, V value, ImmutableMapEntry<K, V> nextInKeyBucket) {
      super(key, value);
      this.nextInKeyBucket = nextInKeyBucket;
   }

   const ImmutableMapEntry<K, V> getNextInKeyBucket() {
      return this.nextInKeyBucket;
   }

    bool isReusable() {
    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
