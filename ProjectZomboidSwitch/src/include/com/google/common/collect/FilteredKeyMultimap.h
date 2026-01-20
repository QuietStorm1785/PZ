#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/FilteredKeyMultimap/AddRejectingList.h"
#include "com/google/common/collect/FilteredKeyMultimap/AddRejectingSet.h"
#include "com/google/common/collect/FilteredKeyMultimap/Entries.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredKeyMultimap {
public:
   const Multimap<K, V> unfiltered;
   const Predicate<? super K> keyPredicate;

   FilteredKeyMultimap(Multimap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      this.unfiltered = (Multimap<K, V>)Preconditions.checkNotNull(unfiltered);
      this.keyPredicate = (Predicate<? super K>)Preconditions.checkNotNull(keyPredicate);
   }

   public Multimap<K, V> unfiltered() {
      return this.unfiltered;
   }

   public Predicate<? super Entry<K, V>> entryPredicate() {
      return Maps.keyPredicateOnEntries(this.keyPredicate);
   }

    int size() {
    int size = 0;

      for (Collection<V> collection : this.asMap().values()) {
         size += collection.size();
      }

    return size;
   }

    bool containsKey(@Nullable Object) {
      return this.unfiltered.containsKey(key) ? this.keyPredicate.apply(key) : false;
   }

   public Collection<V> removeAll(Object key) {
      return this.containsKey(key) ? this.unfiltered.removeAll(key) : this.unmodifiableEmptyCollection();
   }

   Collection<V> unmodifiableEmptyCollection() {
      return (Collection<V>)(this.dynamic_cast<SetMultimap*>(unfiltered) != nullptr ? ImmutableSet.of() : ImmutableList.of());
   }

    void clear() {
      this.keySet().clear();
   }

   Set<K> createKeySet() {
      return Sets.filter(this.unfiltered.keySet(), this.keyPredicate);
   }

   public Collection<V> get(K key) {
      if (this.keyPredicate.apply(key)) {
         return this.unfiltered.get(key);
      } else {
         return (Collection<V>)(this.dynamic_cast<SetMultimap*>(unfiltered) != nullptr ? std::make_shared<AddRejectingSet>(key) : std::make_shared<AddRejectingList>(key));
      }
   }

   Iterator<Entry<K, V>> entryIterator() {
      throw AssertionError("should never be called");
   }

   Collection<Entry<K, V>> createEntries() {
      return std::make_shared<Entries>(this);
   }

   Collection<V> createValues() {
      return std::make_shared<FilteredMultimapValues>(this);
   }

   Map<K, Collection<V>> createAsMap() {
      return Maps.filterKeys(this.unfiltered.asMap(), this.keyPredicate);
   }

   Multiset<K> createKeys() {
      return Multisets.filter(this.unfiltered.keys(), this.keyPredicate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
