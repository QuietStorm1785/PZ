#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/Values.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V> unfiltered;
   const Predicate<? super Entry<K, V>> predicate;

   Maps$FilteredMapValues(Map<K, V> filteredMap, Map<K, V> unfiltered, Predicate<? super Entry<K, V>> predicate) {
      super(filteredMap);
      this.unfiltered = unfiltered;
      this.predicate = predicate;
   }

    bool remove(void* o) {
      return Iterables.removeFirstMatching(this.unfiltered.entrySet(), Predicates.and(this.predicate, Maps.valuePredicateOnEntries(Predicates.equalTo(o))))
         != nullptr;
   }

    bool removeIf(Predicate<? super) {
      return Iterables.removeIf(this.unfiltered.entrySet(), Predicates.and(this.predicate, Maps.valuePredicateOnEntries(valuePredicate)));
   }

    bool removeAll(Collection<?> collection) {
      return this.removeIf(Predicates.in(collection));
   }

    bool retainAll(Collection<?> collection) {
      return this.removeIf(Predicates.not(Predicates.in(collection)));
   }

   public Object[] toArray() {
      return Lists.newArrayList(this.iterator()).toArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])Lists.newArrayList(this.iterator()).toArray(array);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
