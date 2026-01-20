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


class HashBiMap {
public:
    const int keyHash;
    const int valueHash;
   HashBiMap$BiEntry<K, V> nextInKToVBucket;
   HashBiMap$BiEntry<K, V> nextInVToKBucket;
   HashBiMap$BiEntry<K, V> nextInKeyInsertionOrder;
   HashBiMap$BiEntry<K, V> prevInKeyInsertionOrder;

   HashBiMap$BiEntry(K key, int keyHash, V value, int valueHash) {
      super(key, value);
      this.keyHash = keyHash;
      this.valueHash = valueHash;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
