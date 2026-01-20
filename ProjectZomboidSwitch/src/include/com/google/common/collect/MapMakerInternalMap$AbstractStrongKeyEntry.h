#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    const K key;
    const int hash;
    const E next;

   MapMakerInternalMap$AbstractStrongKeyEntry(K key, int hash, @Nullable E next) {
      this.key = key;
      this.hash = hash;
      this.next = next;
   }

    K getKey() {
      return this.key;
   }

    int getHash() {
      return this.hash;
   }

    E getNext() {
      return this.next;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
