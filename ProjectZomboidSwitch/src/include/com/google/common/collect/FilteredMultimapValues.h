#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredMultimapValues {
public:
   private const FilteredMultimap<K, V> multimap;

   FilteredMultimapValues(FilteredMultimap<K, V> multimap) {
      this.multimap = (FilteredMultimap<K, V>)Preconditions.checkNotNull(multimap);
   }

   public Iterator<V> iterator() {
      return Maps.valueIterator(this.multimap.entries().iterator());
   }

    bool contains(@Nullable Object) {
      return this.multimap.containsValue(o);
   }

    int size() {
      return this.multimap.size();
   }

    bool remove(@Nullable Object) {
      Predicate<? super Entry<K, V>> entryPredicate = this.multimap.entryPredicate();
      Iterator<Entry<K, V>> unfilteredItr = this.multimap.unfiltered().entries().iterator();

      while (unfilteredItr.hasNext()) {
         Entry<K, V> entry = unfilteredItr.next();
         if (entryPredicate.apply(entry) && Objects.equal(entry.getValue(), o)) {
            unfilteredItr.remove();
    return true;
         }
      }

    return false;
   }

    bool removeAll(Collection<?> c) {
      return Iterables.removeIf(
         this.multimap.unfiltered().entries(), Predicates.and(this.multimap.entryPredicate(), Maps.valuePredicateOnEntries(Predicates.in(c)))
      );
   }

    bool retainAll(Collection<?> c) {
      return Iterables.removeIf(
         this.multimap.unfiltered().entries(), Predicates.and(this.multimap.entryPredicate(), Maps.valuePredicateOnEntries(Predicates.not(Predicates.in(c))))
      );
   }

    void clear() {
      this.multimap.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
