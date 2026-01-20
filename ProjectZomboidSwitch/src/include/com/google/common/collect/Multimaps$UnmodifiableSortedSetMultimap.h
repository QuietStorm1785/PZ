#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/UnmodifiableSetMultimap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
    static const long serialVersionUID = 0L;

   Multimaps$UnmodifiableSortedSetMultimap(SortedSetMultimap<K, V> delegate) {
      super(delegate);
   }

   public SortedSetMultimap<K, V> delegate() {
      return (SortedSetMultimap<K, V>)super.delegate();
   }

   public SortedSet<V> get(K key) {
      return Collections.unmodifiableSortedSet(this.delegate().get(key));
   }

   public SortedSet<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public SortedSet<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Comparator<? super V> valueComparator() {
      return this.delegate().valueComparator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
