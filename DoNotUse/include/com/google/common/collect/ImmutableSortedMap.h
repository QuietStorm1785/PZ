#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSortedMap/1EntrySet.h"
#include "com/google/common/collect/ImmutableSortedMap/Builder.h"
#include "com/google/common/collect/ImmutableSortedMap/SerializedForm.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMap {
public:
   private static const Comparator<Comparable> NATURAL_ORDER = Ordering.natural();
   private static const ImmutableSortedMap<Comparable, Object> NATURAL_EMPTY_MAP = new ImmutableSortedMap<>(
      ImmutableSortedSet.emptySet(Ordering.natural()), ImmutableList.of()
   );
   private const transient RegularImmutableSortedSet<K> keySet;
   private const transient ImmutableList<V> valueList;
   private transient ImmutableSortedMap<K, V> descendingMap;
    static const long serialVersionUID = 0L;

   static <K, V> ImmutableSortedMap<K, V> emptyMap(Comparator<? super K> comparator) {
      return Ordering.natural() == comparator) ? of() : new ImmutableSortedMap<>(ImmutableSortedSet.emptySet(comparator), ImmutableList.of());
   }

   public static <K, V> ImmutableSortedMap<K, V> of() {
      return (ImmutableSortedMap<K, V>)NATURAL_EMPTY_MAP;
   }

   public static <K : public Comparable<? super K>, V> ImmutableSortedMap<K, V> of(K k1, V v1) {
    return of();
   }

   private static <K, V> ImmutableSortedMap<K, V> of(Comparator<? super K> comparator, K k1, V v1) {
      return new ImmutableSortedMap<>(
    std::make_shared<RegularImmutableSortedSet>();
      );
   }

   private static <K : public Comparable<? super K>, V> ImmutableSortedMap<K, V> ofEntries(ImmutableMapEntry<K, V>... entries) {
    return fromEntries();
   }

   public static <K : public Comparable<? super K>, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2) {
    return ofEntries();
   }

   public static <K : public Comparable<? super K>, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
    return ofEntries();
   }

   public static <K : public Comparable<? super K>, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
    return ofEntries();
   }

   public static <K : public Comparable<? super K>, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
    return ofEntries();
   }

   public static <K, V> ImmutableSortedMap<K, V> copyOf(Map<? : public K, ? : public V> map) {
      Ordering<K> naturalOrder = (Ordering<K>)NATURAL_ORDER;
    return copyOfInternal();
   }

   public static <K, V> ImmutableSortedMap<K, V> copyOf(Map<? : public K, ? : public V> map, Comparator<? super K> comparator) {
    return copyOfInternal((Comparator<? super);
   }

   public static <K, V> ImmutableSortedMap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      Ordering<K> naturalOrder = (Ordering<K>)NATURAL_ORDER;
    return copyOf();
   }

   public static <K, V> ImmutableSortedMap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries, Comparator<? super K> comparator) {
    return fromEntries((Comparator<? super);
   }

   public static <K, V> ImmutableSortedMap<K, V> copyOfSorted(SortedMap<K, ? : public V> map) {
      Comparator<? super K> comparator = map.comparator();
      if (comparator == nullptr) {
         comparator = NATURAL_ORDER;
      }

      if (dynamic_cast<ImmutableSortedMap*>(map) != nullptr) {
         ImmutableSortedMap<K, V> kvMap = (ImmutableSortedMap<K, V>)map;
         if (!kvMap.isPartialView()) {
    return kvMap;
         }
      }

    return fromEntries();
   }

   private static <K, V> ImmutableSortedMap<K, V> copyOfInternal(Map<? : public K, ? : public V> map, Comparator<? super K> comparator) {
    bool sameComparator = false;
      if (dynamic_cast<SortedMap*>(map) != nullptr) {
         SortedMap<?, ?> sortedMap = (SortedMap<?, ?>)map;
         Comparator<?> comparator2 = sortedMap.comparator();
         sameComparator = comparator2 == nullptr ? comparator == NATURAL_ORDER : comparator == comparator2);
      }

      if (sameComparator && dynamic_cast<ImmutableSortedMap*>(map) != nullptr) {
         ImmutableSortedMap<K, V> kvMap = (ImmutableSortedMap<K, V>)map;
         if (!kvMap.isPartialView()) {
    return kvMap;
         }
      }

    return fromEntries();
   }

   private static <K, V> ImmutableSortedMap<K, V> fromEntries(
      Comparator<? super K> comparator, boolean sameComparator, Iterable<? : public Entry<? : public K, ? : public V>> entries
   ) {
      Entry<K, V>[] entryArray = (Entry<K, V>[])Iterables.toArray(entries, EMPTY_ENTRY_ARRAY);
    return fromEntries();
   }

   private static <K, V> ImmutableSortedMap<K, V> fromEntries(Comparator<? super K> comparator, boolean sameComparator, Entry<K, V>[] entryArray, int size) {
      switch (size) {
         case 0:
    return emptyMap();
         case 1:
    return of();
         default:
            Object[] keys = new Object[size];
            Object[] values = new Object[size];
            if (sameComparator) {
               for (int i = 0; i < size; i++) {
    void* key = entryArray[i].getKey();
    void* value = entryArray[i].getValue();
                  CollectPreconditions.checkEntryNotNull(key, value);
                  keys[i] = key;
                  values[i] = value;
               }
            } else {
               Arrays.sort(entryArray, 0, size, Ordering.from(comparator).onKeys());
    K prevKey = entryArray[0].getKey();
               keys[0] = prevKey;
               values[0] = entryArray[0].getValue();

               for (int i = 1; i < size; i++) {
    K key = entryArray[i].getKey();
    V value = entryArray[i].getValue();
                  CollectPreconditions.checkEntryNotNull(key, value);
                  keys[i] = key;
                  values[i] = value;
                  checkNoConflict(comparator.compare(prevKey, key) != 0, "key", entryArray[i - 1], entryArray[i]);
                  prevKey = key;
               }
            }

            return new ImmutableSortedMap<>(std::make_shared<RegularImmutableSortedSet>(std::make_shared<RegularImmutableList>(keys), comparator), std::make_shared<RegularImmutableList>(values));
      }
   }

   public static <K : public Comparable<?>, V> Builder<K, V> naturalOrder() {
      return std::make_shared<Builder>(Ordering.natural());
   }

   public static <K, V> Builder<K, V> orderedBy(Comparator<K> comparator) {
      return std::make_shared<Builder>(comparator);
   }

   public static <K : public Comparable<?>, V> Builder<K, V> reverseOrder() {
      return std::make_shared<Builder>(Ordering.natural().reverse());
   }

   ImmutableSortedMap(RegularImmutableSortedSet<K> keySet, ImmutableList<V> valueList) {
      this(keySet, valueList, nullptr);
   }

   ImmutableSortedMap(RegularImmutableSortedSet<K> keySet, ImmutableList<V> valueList, ImmutableSortedMap<K, V> descendingMap) {
      this.keySet = keySet;
      this.valueList = valueList;
      this.descendingMap = descendingMap;
   }

    int size() {
      return this.valueList.size();
   }

    V get(@Nullable Object) {
    int index = this.keySet.indexOf(key);
      return (V)(index == -1 ? nullptr : this.valueList.get(index));
   }

    bool isPartialView() {
      return this.keySet.isPartialView() || this.valueList.isPartialView();
   }

   public ImmutableSet<Entry<K, V>> entrySet() {
      return super.entrySet();
   }

   ImmutableSet<Entry<K, V>> createEntrySet() {
      return (ImmutableSet<Entry<K, V>>)(this.empty() ? ImmutableSet.of() : std::make_shared<1EntrySet>(this));
   }

   public ImmutableSortedSet<K> keySet() {
      return this.keySet;
   }

   public ImmutableCollection<V> values() {
      return this.valueList;
   }

   public Comparator<? super K> comparator() {
      return this.keySet().comparator();
   }

    K firstKey() {
      return (K)this.keySet().first();
   }

    K lastKey() {
      return (K)this.keySet().last();
   }

   private ImmutableSortedMap<K, V> getSubMap(int fromIndex, int toIndex) {
      if (fromIndex == 0 && toIndex == this.size()) {
    return this;
      } else {
         return fromIndex == toIndex
            ? emptyMap(this.comparator())
            : new ImmutableSortedMap<>(this.keySet.getSubSet(fromIndex, toIndex), this.valueList.subList(fromIndex, toIndex));
      }
   }

   public ImmutableSortedMap<K, V> headMap(K toKey) {
      return this.headMap(toKey, false);
   }

   public ImmutableSortedMap<K, V> headMap(K toKey, boolean inclusive) {
      return this.getSubMap(0, this.keySet.headIndex(Preconditions.checkNotNull(toKey), inclusive));
   }

   public ImmutableSortedMap<K, V> subMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public ImmutableSortedMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      Preconditions.checkNotNull(fromKey);
      Preconditions.checkNotNull(toKey);
      Preconditions.checkArgument(this.comparator().compare(fromKey, toKey) <= 0, "expected fromKey <= toKey but %s > %s", fromKey, toKey);
      return this.headMap(toKey, toInclusive).tailMap(fromKey, fromInclusive);
   }

   public ImmutableSortedMap<K, V> tailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }

   public ImmutableSortedMap<K, V> tailMap(K fromKey, boolean inclusive) {
      return this.getSubMap(this.keySet.tailIndex(Preconditions.checkNotNull(fromKey), inclusive), this.size());
   }

   public Entry<K, V> lowerEntry(K key) {
      return this.headMap(key, false).lastEntry();
   }

    K lowerKey(K key) {
      return (K)Maps.keyOrNull(this.lowerEntry(key));
   }

   public Entry<K, V> floorEntry(K key) {
      return this.headMap(key, true).lastEntry();
   }

    K floorKey(K key) {
      return (K)Maps.keyOrNull(this.floorEntry(key));
   }

   public Entry<K, V> ceilingEntry(K key) {
      return this.tailMap(key, true).firstEntry();
   }

    K ceilingKey(K key) {
      return (K)Maps.keyOrNull(this.ceilingEntry(key));
   }

   public Entry<K, V> higherEntry(K key) {
      return this.tailMap(key, false).firstEntry();
   }

    K higherKey(K key) {
      return (K)Maps.keyOrNull(this.higherEntry(key));
   }

   public Entry<K, V> firstEntry() {
      return this.empty() ? nullptr : (Entry)this.entrySet().asList().get(0);
   }

   public Entry<K, V> lastEntry() {
      return this.empty() ? nullptr : (Entry)this.entrySet().asList().get(this.size() - 1);
   }

   public const Entry<K, V> pollFirstEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public const Entry<K, V> pollLastEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableSortedMap<K, V> descendingMap() {
      ImmutableSortedMap<K, V> result = this.descendingMap;
      if (result == nullptr) {
         return this.empty()
            ? emptyMap(Ordering.from(this.comparator()).reverse())
            : new ImmutableSortedMap<>((RegularImmutableSortedSet<K>)this.keySet.descendingSet(), this.valueList.reverse(), this);
      } else {
    return result;
      }
   }

   public ImmutableSortedSet<K> navigableKeySet() {
      return this.keySet;
   }

   public ImmutableSortedSet<K> descendingKeySet() {
      return this.keySet.descendingSet();
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
