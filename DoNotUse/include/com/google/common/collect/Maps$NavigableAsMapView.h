#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const NavigableSet<K> set;
   private const Function<? super K, V> function;

   Maps$NavigableAsMapView(NavigableSet<K> ks, Function<? super K, V> vFunction) {
      this.set = (NavigableSet<K>)Preconditions.checkNotNull(ks);
      this.function = (Function<? super K, V>)Preconditions.checkNotNull(vFunction);
   }

   public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return Maps.asMap(this.set.subSet(fromKey, fromInclusive, toKey, toInclusive), this.function);
   }

   public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
      return Maps.asMap(this.set.headSet(toKey, inclusive), this.function);
   }

   public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
      return Maps.asMap(this.set.tailSet(fromKey, inclusive), this.function);
   }

   public Comparator<? super K> comparator() {
      return this.set.comparator();
   }

    V get(@Nullable Object) {
      return (V)(Collections2.safeContains(this.set, key) ? this.function.apply(key) : nullptr);
   }

    void clear() {
      this.set.clear();
   }

   Iterator<Entry<K, V>> entryIterator() {
      return Maps.asMapEntryIterator(this.set, this.function);
   }

   Iterator<Entry<K, V>> descendingEntryIterator() {
      return this.descendingMap().entrySet().iterator();
   }

   public NavigableSet<K> navigableKeySet() {
      return Maps.access$400(this.set);
   }

    int size() {
      return this.set.size();
   }

   public NavigableMap<K, V> descendingMap() {
      return Maps.asMap(this.set.descendingSet(), this.function);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
