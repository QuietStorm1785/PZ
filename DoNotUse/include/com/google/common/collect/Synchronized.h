#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/Synchronized/SynchronizedBiMap.h"
#include "com/google/common/collect/Synchronized/SynchronizedCollection.h"
#include "com/google/common/collect/Synchronized/SynchronizedDeque.h"
#include "com/google/common/collect/Synchronized/SynchronizedEntry.h"
#include "com/google/common/collect/Synchronized/SynchronizedList.h"
#include "com/google/common/collect/Synchronized/SynchronizedListMultimap.h"
#include "com/google/common/collect/Synchronized/SynchronizedMap.h"
#include "com/google/common/collect/Synchronized/SynchronizedMultimap.h"
#include "com/google/common/collect/Synchronized/SynchronizedMultiset.h"
#include "com/google/common/collect/Synchronized/SynchronizedNavigableMap.h"
#include "com/google/common/collect/Synchronized/SynchronizedNavigableSet.h"
#include "com/google/common/collect/Synchronized/SynchronizedQueue.h"
#include "com/google/common/collect/Synchronized/SynchronizedRandomAccessList.h"
#include "com/google/common/collect/Synchronized/SynchronizedSet.h"
#include "com/google/common/collect/Synchronized/SynchronizedSetMultimap.h"
#include "com/google/common/collect/Synchronized/SynchronizedSortedMap.h"
#include "com/google/common/collect/Synchronized/SynchronizedSortedSet.h"
#include "com/google/common/collect/Synchronized/SynchronizedSortedSetMultimap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    private Synchronized() {
   }

   private static <E> Collection<E> collection(Collection<E> collection, @Nullable Object mutex) {
      return std::make_shared<SynchronizedCollection>(collection, mutex, nullptr);
   }

   static <E> Set<E> set(Set<E> set, @Nullable Object mutex) {
      return std::make_shared<SynchronizedSet>(set, mutex);
   }

   private static <E> SortedSet<E> sortedSet(SortedSet<E> set, @Nullable Object mutex) {
      return std::make_shared<SynchronizedSortedSet>(set, mutex);
   }

   private static <E> List<E> list(List<E> list, @Nullable Object mutex) {
      return (List<E>)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<SynchronizedRandomAccessList>(list, mutex) : std::make_shared<SynchronizedList>(list, mutex));
   }

   static <E> Multiset<E> multiset(Multiset<E> multiset, @Nullable Object mutex) {
      return (Multiset<E>)(!(dynamic_cast<SynchronizedMultiset*>(multiset) != nullptr) && !(dynamic_cast<ImmutableMultiset*>(multiset) != nullptr)
         ? std::make_shared<SynchronizedMultiset>(multiset, mutex)
         : multiset);
   }

   static <K, V> Multimap<K, V> multimap(Multimap<K, V> multimap, @Nullable Object mutex) {
      return (Multimap<K, V>)(!(dynamic_cast<SynchronizedMultimap*>(multimap) != nullptr) && !(dynamic_cast<ImmutableMultimap*>(multimap) != nullptr)
         ? std::make_shared<SynchronizedMultimap>(multimap, mutex)
         : multimap);
   }

   static <K, V> ListMultimap<K, V> listMultimap(ListMultimap<K, V> multimap, @Nullable Object mutex) {
      return (ListMultimap<K, V>)(!(dynamic_cast<SynchronizedListMultimap*>(multimap) != nullptr) && !(dynamic_cast<ImmutableListMultimap*>(multimap) != nullptr)
         ? std::make_shared<SynchronizedListMultimap>(multimap, mutex)
         : multimap);
   }

   static <K, V> SetMultimap<K, V> setMultimap(SetMultimap<K, V> multimap, @Nullable Object mutex) {
      return (SetMultimap<K, V>)(!(dynamic_cast<SynchronizedSetMultimap*>(multimap) != nullptr) && !(dynamic_cast<ImmutableSetMultimap*>(multimap) != nullptr)
         ? std::make_shared<SynchronizedSetMultimap>(multimap, mutex)
         : multimap);
   }

   static <K, V> SortedSetMultimap<K, V> sortedSetMultimap(SortedSetMultimap<K, V> multimap, @Nullable Object mutex) {
      return (SortedSetMultimap<K, V>)(dynamic_cast<SynchronizedSortedSetMultimap*>(multimap) != nullptr ? multimap : std::make_shared<SynchronizedSortedSetMultimap>(multimap, mutex));
   }

   private static <E> Collection<E> typePreservingCollection(Collection<E> collection, @Nullable Object mutex) {
      if (dynamic_cast<SortedSet*>(collection) != nullptr) {
    return sortedSet();
      } else if (dynamic_cast<Set*>(collection) != nullptr) {
    return set();
      } else {
         return (Collection<E>)(dynamic_cast<List*>(collection) != nullptr ? list((List<E>)collection, mutex) : collection(collection, mutex));
      }
   }

   private static <E> Set<E> typePreservingSet(Set<E> set, @Nullable Object mutex) {
      return (Set<E>)(dynamic_cast<SortedSet*>(set) != nullptr ? sortedSet((SortedSet<E>)set, mutex) : set(set, mutex));
   }

   static <K, V> Map<K, V> map(Map<K, V> map, @Nullable Object mutex) {
      return std::make_shared<SynchronizedMap>(map, mutex);
   }

   static <K, V> SortedMap<K, V> sortedMap(SortedMap<K, V> sortedMap, @Nullable Object mutex) {
      return std::make_shared<SynchronizedSortedMap>(sortedMap, mutex);
   }

   static <K, V> BiMap<K, V> biMap(BiMap<K, V> bimap, @Nullable Object mutex) {
      return (BiMap<K, V>)(!(dynamic_cast<SynchronizedBiMap*>(bimap) != nullptr) && !(dynamic_cast<ImmutableBiMap*>(bimap) != nullptr)
         ? std::make_shared<SynchronizedBiMap>(bimap, mutex, nullptr, nullptr)
         : bimap);
   }

   static <E> NavigableSet<E> navigableSet(NavigableSet<E> navigableSet, @Nullable Object mutex) {
      return std::make_shared<SynchronizedNavigableSet>(navigableSet, mutex);
   }

   static <E> NavigableSet<E> navigableSet(NavigableSet<E> navigableSet) {
    return navigableSet();
   }

   static <K, V> NavigableMap<K, V> navigableMap(NavigableMap<K, V> navigableMap) {
    return navigableMap();
   }

   static <K, V> NavigableMap<K, V> navigableMap(NavigableMap<K, V> navigableMap, @Nullable Object mutex) {
      return std::make_shared<SynchronizedNavigableMap>(navigableMap, mutex);
   }

   private static <K, V> Entry<K, V> nullableSynchronizedEntry(@Nullable Entry<K, V> entry, @Nullable Object mutex) {
    return entry = = nullptr ? nullptr : std::make_shared<SynchronizedEntry>(entry, mutex);
   }

   static <E> std::queue<E> queue(std::queue<E> queue, @Nullable Object mutex) {
      return (std::queue<E>)(dynamic_cast<SynchronizedQueue*>(queue) != nullptr ? queue : std::make_shared<SynchronizedQueue>(queue, mutex));
   }

   static <E> std::deque<E> deque(std::deque<E> deque, @Nullable Object mutex) {
      return std::make_shared<SynchronizedDeque>(deque, mutex);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
