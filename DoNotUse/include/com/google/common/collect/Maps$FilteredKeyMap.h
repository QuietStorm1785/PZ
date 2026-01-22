#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/AbstractFilteredMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Predicate<? super K> keyPredicate;

   Maps$FilteredKeyMap(Map<K, V> unfiltered, Predicate<? super K> keyPredicate, Predicate<? super Entry<K, V>> entryPredicate) {
      super(unfiltered, entryPredicate);
      this.keyPredicate = keyPredicate;
   }

   protected Set<Entry<K, V>> createEntrySet() {
      return Sets.filter(this.unfiltered.entrySet(), this.predicate);
   }

   Set<K> createKeySet() {
      return Sets.filter(this.unfiltered.keySet(), this.keyPredicate);
   }

    bool containsKey(void* key) {
      return this.unfiltered.containsKey(key) && this.keyPredicate.apply(key);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
