#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace graph {

class MapRetrievalCache {
public:
    const K key;
    const V value;

   MapRetrievalCache$CacheEntry(K key, V value) {
      this.key = key;
      this.value = value;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
