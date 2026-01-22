#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredKeyMultimap {
public:
    const K key;

   FilteredKeyMultimap$AddRejectingList(K key) {
      this.key = key;
   }

    bool add(V v) {
      this.push_back(0, v);
    return true;
   }

    bool addAll(Collection<? extends) {
      this.addAll(0, collection);
    return true;
   }

    void add(int index, V element) {
      Preconditions.checkPositionIndex(index, 0);
      throw IllegalArgumentException("Key does not satisfy predicate: " + this.key);
   }

    bool addAll(int index, Collection<? extends) {
      Preconditions.checkNotNull(elements);
      Preconditions.checkPositionIndex(index, 0);
      throw IllegalArgumentException("Key does not satisfy predicate: " + this.key);
   }

   protected List<V> delegate() {
      return Collections.emptyList();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
