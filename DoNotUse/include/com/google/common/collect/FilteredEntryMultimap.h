#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap.h"
#include "com/google/common/collect/FilteredEntryMultimap/Keys.h"
#include "com/google/common/collect/FilteredEntryMultimap/ValuePredicate.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   const Multimap<K, V> unfiltered;
   const Predicate<? super Entry<K, V>> predicate;

   FilteredEntryMultimap(Multimap<K, V> unfiltered, Predicate<? super Entry<K, V>> predicate) {
      this.unfiltered = (Multimap<K, V>)Preconditions.checkNotNull(unfiltered);
      this.predicate = (Predicate<? super Entry<K, V>>)Preconditions.checkNotNull(predicate);
   }

   public Multimap<K, V> unfiltered() {
      return this.unfiltered;
   }

   public Predicate<? super Entry<K, V>> entryPredicate() {
      return this.predicate;
   }

    int size() {
      return this.entries().size();
   }

    bool satisfies(K key, V value) {
      return this.predicate.apply(Maps.immutableEntry(key, value));
   }

   static <E> Collection<E> filterCollection(Collection<E> collection, Predicate<? super E> predicate) {
      return (Collection<E>)(dynamic_cast<Set*>(collection) != nullptr ? Sets.filter((Set)collection, predicate) : Collections2.filter(collection, predicate));
   }

    bool containsKey(@Nullable Object) {
      return this.asMap().get(key) != nullptr;
   }

   public Collection<V> removeAll(@Nullable Object key) {
      return (Collection<V>)MoreObjects.firstNonNull(this.asMap().remove(key), this.unmodifiableEmptyCollection());
   }

   Collection<V> unmodifiableEmptyCollection() {
      return (Collection<V>)(this.dynamic_cast<SetMultimap*>(unfiltered) != nullptr ? Collections.emptySet() : Collections.emptyList());
   }

    void clear() {
      this.entries().clear();
   }

   public Collection<V> get(K key) {
    return filterCollection();
   }

   Collection<Entry<K, V>> createEntries() {
    return filterCollection();
   }

   Collection<V> createValues() {
      return std::make_shared<FilteredMultimapValues>(this);
   }

   Iterator<Entry<K, V>> entryIterator() {
      throw AssertionError("should never be called");
   }

   Map<K, Collection<V>> createAsMap() {
      return std::make_shared<AsMap>(this);
   }

   public Set<K> keySet() {
      return this.asMap().keySet();
   }

    bool removeEntriesIf(Predicate<? super, Collection<V>>> predicate) {
      Iterator<Entry<K, Collection<V>>> entryIterator = this.unfiltered.asMap().entrySet().iterator();
    bool changed = false;

      while (entryIterator.hasNext()) {
         Entry<K, Collection<V>> entry = entryIterator.next();
    K key = entry.getKey();
         Collection<V> collection = filterCollection(entry.getValue(), std::make_shared<ValuePredicate>(this, key));
         if (!collection.empty() && predicate.apply(Maps.immutableEntry(key, collection))) {
            if (collection.size() == entry.getValue().size()) {
               entryIterator.remove();
            } else {
               collection.clear();
            }

            changed = true;
         }
      }

    return changed;
   }

   Multiset<K> createKeys() {
      return std::make_shared<Keys>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
