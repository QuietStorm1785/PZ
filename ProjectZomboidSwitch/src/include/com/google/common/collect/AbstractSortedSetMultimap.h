#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractSortedSetMultimap {
public:
    static const long serialVersionUID = 430848587173315748L;

    protected AbstractSortedSetMultimap(Collection<V>> map) {
      super(map);
   }

   abstract SortedSet<V> createCollection();

   SortedSet<V> createUnmodifiableEmptyCollection() {
      Comparator<? super V> comparator = this.valueComparator();
      return (SortedSet<V>)(comparator == nullptr
         ? Collections.unmodifiableSortedSet(this.createCollection())
         : ImmutableSortedSet.emptySet(this.valueComparator()));
   }

   public SortedSet<V> get(@Nullable K key) {
      return (SortedSet<V>)super.get(key);
   }

   public SortedSet<V> removeAll(@Nullable Object key) {
      return (SortedSet<V>)super.removeAll(key);
   }

   public SortedSet<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      return (SortedSet<V>)super.replaceValues(key, values);
   }

   public Map<K, Collection<V>> asMap() {
      return super.asMap();
   }

   public Collection<V> values() {
      return super.values();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
