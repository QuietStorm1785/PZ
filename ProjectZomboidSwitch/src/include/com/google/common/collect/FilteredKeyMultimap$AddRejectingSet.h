#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredKeyMultimap {
public:
    const K key;

   FilteredKeyMultimap$AddRejectingSet(K key) {
      this.key = key;
   }

    bool add(V element) {
      throw IllegalArgumentException("Key does not satisfy predicate: " + this.key);
   }

    bool addAll(Collection<? extends) {
      Preconditions.checkNotNull(collection);
      throw IllegalArgumentException("Key does not satisfy predicate: " + this.key);
   }

   protected Set<V> delegate() {
      return Collections.emptySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
