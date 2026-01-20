#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Predicate.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntrySetMultimap {
public:
   FilteredEntrySetMultimap(SetMultimap<K, V> unfiltered, Predicate<? super Entry<K, V>> predicate) {
      super(unfiltered, predicate);
   }

   public SetMultimap<K, V> unfiltered() {
      return (SetMultimap<K, V>)this.unfiltered;
   }

   public Set<V> get(K key) {
      return (Set<V>)super.get(key);
   }

   public Set<V> removeAll(Object key) {
      return (Set<V>)super.removeAll(key);
   }

   public Set<V> replaceValues(K key, Iterable<? : public V> values) {
      return (Set<V>)super.replaceValues(key, values);
   }

   Set<Entry<K, V>> createEntries() {
      return Sets.filter(this.unfiltered().entries(), this.entryPredicate());
   }

   public Set<Entry<K, V>> entries() {
      return (Set<Entry<K, V>>)super.entries();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
