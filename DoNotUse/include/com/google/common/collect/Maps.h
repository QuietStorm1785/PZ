#pragma once
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Converter.h"
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Joiner/MapJoiner.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/collect/MapDifference/ValueDifference.h"
#include "com/google/common/collect/Maps/1.h"
#include "com/google/common/collect/Maps/10.h"
#include "com/google/common/collect/Maps/11.h"
#include "com/google/common/collect/Maps/2.h"
#include "com/google/common/collect/Maps/3.h"
#include "com/google/common/collect/Maps/4.h"
#include "com/google/common/collect/Maps/5.h"
#include "com/google/common/collect/Maps/6.h"
#include "com/google/common/collect/Maps/7.h"
#include "com/google/common/collect/Maps/8.h"
#include "com/google/common/collect/Maps/9.h"
#include "com/google/common/collect/Maps/AbstractFilteredMap.h"
#include "com/google/common/collect/Maps/AsMapView.h"
#include "com/google/common/collect/Maps/BiMapConverter.h"
#include "com/google/common/collect/Maps/EntryFunction.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Maps/FilteredEntryBiMap.h"
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/common/collect/Maps/FilteredEntryNavigableMap.h"
#include "com/google/common/collect/Maps/FilteredEntrySortedMap.h"
#include "com/google/common/collect/Maps/FilteredKeyMap.h"
#include "com/google/common/collect/Maps/MapDifferenceImpl.h"
#include "com/google/common/collect/Maps/NavigableAsMapView.h"
#include "com/google/common/collect/Maps/SortedAsMapView.h"
#include "com/google/common/collect/Maps/SortedMapDifferenceImpl.h"
#include "com/google/common/collect/Maps/TransformedEntriesMap.h"
#include "com/google/common/collect/Maps/TransformedEntriesNavigableMap.h"
#include "com/google/common/collect/Maps/TransformedEntriesSortedMap.h"
#include "com/google/common/collect/Maps/UnmodifiableBiMap.h"
#include "com/google/common/collect/Maps/UnmodifiableEntrySet.h"
#include "com/google/common/collect/Maps/UnmodifiableNavigableMap.h"
#include "com/google/common/collect/Maps/ValueDifferenceImpl.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
    static const MapJoiner STANDARD_JOINER = Collections2.STANDARD_JOINER.withKeyValueSeparator("=");

    private Maps() {
   }

   static <K> Function<Entry<K, ?>, K> keyFunction() {
      return EntryFunction.KEY;
   }

   static <V> Function<Entry<?, V>, V> valueFunction() {
      return EntryFunction.VALUE;
   }

   static <K, V> Iterator<K> keyIterator(Iterator<Entry<K, V>> entryIterator) {
      return Iterators.transform(entryIterator, keyFunction());
   }

   static <K, V> Iterator<V> valueIterator(Iterator<Entry<K, V>> entryIterator) {
      return Iterators.transform(entryIterator, valueFunction());
   }

   public static <K : public Enum<K>, V> ImmutableMap<K, V> immutableEnumMap(Map<K, ? : public V> map) {
      if (dynamic_cast<ImmutableEnumMap*>(map) != nullptr) {
         return (ImmutableEnumMap)map;
      } else if (map.empty()) {
         return ImmutableMap.of();
      } else {
         for (Entry<K, ? : public V> entry : map.entrySet()) {
            Preconditions.checkNotNull(entry.getKey());
            Preconditions.checkNotNull(entry.getValue());
         }

         return ImmutableEnumMap.asImmutable(new EnumMap<>(map));
      }
   }

   public static <K, V> std::unordered_map<K, V> newHashMap() {
      return std::make_unique<std::unordered_map<>>();
   }

   public static <K, V> std::unordered_map<K, V> newHashMapWithExpectedSize(int expectedSize) {
      return new std::unordered_map<>(capacity(expectedSize));
   }

    static int capacity(int expectedSize) {
      if (expectedSize < 3) {
         CollectPreconditions.checkNonnegative(expectedSize, "expectedSize");
         return expectedSize + 1;
      } else {
         return expectedSize < 1073741824 ? (int)(expectedSize / 0.75F + 1.0F) : int.MAX_VALUE;
      }
   }

   public static <K, V> std::unordered_map<K, V> newHashMap(Map<? : public K, ? : public V> map) {
      return new std::unordered_map<>(map);
   }

   public static <K, V> LinkedHashMap<K, V> newLinkedHashMap() {
      return std::make_unique<LinkedHashMap<>>();
   }

   public static <K, V> LinkedHashMap<K, V> newLinkedHashMapWithExpectedSize(int expectedSize) {
      return new LinkedHashMap<>(capacity(expectedSize));
   }

   public static <K, V> LinkedHashMap<K, V> newLinkedHashMap(Map<? : public K, ? : public V> map) {
      return new LinkedHashMap<>(map);
   }

   public static <K, V> ConcurrentMap<K, V> newConcurrentMap() {
      return std::make_unique<MapMaker>().makeMap();
   }

   public static <K : public Comparable, V> std::map<K, V> newTreeMap() {
      return std::make_unique<std::map<>>();
   }

   public static <K, V> std::map<K, V> newTreeMap(SortedMap<K, ? : public V> map) {
      return new std::map<>(map);
   }

   public static <C, K : public C, V> std::map<K, V> newTreeMap(@Nullable Comparator<C> comparator) {
      return new std::map<>(comparator);
   }

   public static <K : public Enum<K>, V> EnumMap<K, V> newEnumMap(Class<K> type) {
      return new EnumMap<>((Class<K>)Preconditions.checkNotNull(type));
   }

   public static <K : public Enum<K>, V> EnumMap<K, V> newEnumMap(Map<K, ? : public V> map) {
      return new EnumMap<>(map);
   }

   public static <K, V> IdentityHashMap<K, V> newIdentityHashMap() {
      return std::make_unique<IdentityHashMap<>>();
   }

   public static <K, V> MapDifference<K, V> difference(Map<? : public K, ? : public V> left, Map<? : public K, ? : public V> right) {
      if (dynamic_cast<SortedMap*>(left) != nullptr) {
         SortedMap<K, ? : public V> sortedLeft = (SortedMap<K, ? : public V>)left;
    return difference();
      } else {
    return difference();
      }
   }

   public static <K, V> MapDifference<K, V> difference(
      Map<? : public K, ? : public V> left, Map<? : public K, ? : public V> right, Equivalence<? super V> valueEquivalence
   ) {
      Preconditions.checkNotNull(valueEquivalence);
      Map<K, V> onlyOnLeft = newLinkedHashMap();
      Map<K, V> onlyOnRight = new LinkedHashMap<>(right);
      Map<K, V> onBoth = newLinkedHashMap();
      Map<K, ValueDifference<V>> differences = newLinkedHashMap();
      doDifference(left, right, valueEquivalence, onlyOnLeft, onlyOnRight, onBoth, differences);
      return std::make_shared<MapDifferenceImpl>(onlyOnLeft, onlyOnRight, onBoth, differences);
   }

   private static <K, V> void doDifference(
      Map<? : public K, ? : public V> left,
      Map<? : public K, ? : public V> right,
      Equivalence<? super V> valueEquivalence,
      Map<K, V> onlyOnLeft,
      Map<K, V> onlyOnRight,
      Map<K, V> onBoth,
      Map<K, ValueDifference<V>> differences
   ) {
      for (Entry<? : public K, ? : public V> entry : left.entrySet()) {
    K leftKey = (K)entry.getKey();
    V leftValue = (V)entry.getValue();
         if (right.containsKey(leftKey)) {
    V rightValue = onlyOnRight.remove(leftKey);
            if (valueEquivalence.equivalent(leftValue, rightValue)) {
               onBoth.put(leftKey, leftValue);
            } else {
               differences.put(leftKey, ValueDifferenceImpl.create(leftValue, rightValue));
            }
         } else {
            onlyOnLeft.put(leftKey, leftValue);
         }
      }
   }

   private static <K, V> Map<K, V> unmodifiableMap(Map<K, ? : public V> map) {
      return (Map<K, V>)(dynamic_cast<SortedMap*>(map) != nullptr ? Collections.unmodifiableSortedMap((SortedMap<K, ? : public V>)map) : Collections.unmodifiableMap(map));
   }

   public static <K, V> SortedMapDifference<K, V> difference(SortedMap<K, ? : public V> left, Map<? : public K, ? : public V> right) {
      Preconditions.checkNotNull(left);
      Preconditions.checkNotNull(right);
      Comparator<? super K> comparator = orNaturalOrder(left.comparator());
      SortedMap<K, V> onlyOnLeft = newTreeMap(comparator);
      SortedMap<K, V> onlyOnRight = newTreeMap(comparator);
      onlyOnRight.putAll(right);
      SortedMap<K, V> onBoth = newTreeMap(comparator);
      SortedMap<K, ValueDifference<V>> differences = newTreeMap(comparator);
      doDifference(left, right, Equivalence == ), onlyOnLeft, onlyOnRight, onBoth, differences);
      return std::make_shared<SortedMapDifferenceImpl>(onlyOnLeft, onlyOnRight, onBoth, differences);
   }

   static <E> Comparator<? super E> orNaturalOrder(@Nullable Comparator<? super E> comparator) {
      return (Comparator<? super E>)(comparator != nullptr ? comparator : Ordering.natural());
   }

   public static <K, V> Map<K, V> asMap(Set<K> set, Function<? super K, V> function) {
      return std::make_shared<AsMapView>(set, function);
   }

   public static <K, V> SortedMap<K, V> asMap(SortedSet<K> set, Function<? super K, V> function) {
      return std::make_shared<SortedAsMapView>(set, function);
   }

   public static <K, V> NavigableMap<K, V> asMap(NavigableSet<K> set, Function<? super K, V> function) {
      return std::make_shared<NavigableAsMapView>(set, function);
   }

   static <K, V> Iterator<Entry<K, V>> asMapEntryIterator(Set<K> set, Function<? super K, V> function) {
      return std::make_shared<1>(set.iterator(), function);
   }

   private static <E> Set<E> removeOnlySet(Set<E> set) {
      return std::make_shared<2>(set);
   }

   private static <E> SortedSet<E> removeOnlySortedSet(SortedSet<E> set) {
      return std::make_shared<3>(set);
   }

   private static <E> NavigableSet<E> removeOnlyNavigableSet(NavigableSet<E> set) {
      return std::make_shared<4>(set);
   }

   public static <K, V> ImmutableMap<K, V> toMap(Iterable<K> keys, Function<? super K, V> valueFunction) {
    return toMap();
   }

   public static <K, V> ImmutableMap<K, V> toMap(Iterator<K> keys, Function<? super K, V> valueFunction) {
      Preconditions.checkNotNull(valueFunction);
      Map<K, V> builder = newLinkedHashMap();

      while (keys.hasNext()) {
    K key = keys.next();
         builder.put(key, (V)valueFunction.apply(key));
      }

      return ImmutableMap.copyOf(builder);
   }

   public static <K, V> ImmutableMap<K, V> uniqueIndex(Iterable<V> values, Function<? super V, K> keyFunction) {
    return uniqueIndex();
   }

   public static <K, V> ImmutableMap<K, V> uniqueIndex(Iterator<V> values, Function<? super V, K> keyFunction) {
      Preconditions.checkNotNull(keyFunction);
      Builder<K, V> builder = ImmutableMap.builder();

      while (values.hasNext()) {
    V value = values.next();
         builder.put(keyFunction.apply(value), value);
      }

      try {
         return builder.build();
      } catch (IllegalArgumentException var4) {
         throw IllegalArgumentException(var4.getMessage() + ". To index multiple values under a key, use Multimaps.index.");
      }
   }

   public static ImmutableMap<std::string, std::string> fromProperties(Properties properties) {
      Builder<std::string, std::string> builder = ImmutableMap.builder();
      Enumeration<?> e = properties.propertyNames();

      while (e.hasMoreElements()) {
    std::string key = (std::string)e.nextElement();
         builder.put(key, properties.getProperty(key));
      }

      return builder.build();
   }

   public static <K, V> Entry<K, V> immutableEntry(@Nullable K key, @Nullable V value) {
      return std::make_shared<ImmutableEntry>(key, value);
   }

   static <K, V> Set<Entry<K, V>> unmodifiableEntrySet(Set<Entry<K, V>> entrySet) {
      return std::make_shared<UnmodifiableEntrySet>(Collections.unmodifiableSet(entrySet));
   }

   static <K, V> Entry<K, V> unmodifiableEntry(Entry<? : public K, ? : public V> entry) {
      Preconditions.checkNotNull(entry);
      return std::make_shared<5>(entry);
   }

   static <K, V> UnmodifiableIterator<Entry<K, V>> unmodifiableEntryIterator(Iterator<Entry<K, V>> entryIterator) {
      return std::make_shared<6>(entryIterator);
   }

   public static <A, B> Converter<A, B> asConverter(BiMap<A, B> bimap) {
      return std::make_shared<BiMapConverter>(bimap);
   }

   public static <K, V> BiMap<K, V> synchronizedBiMap(BiMap<K, V> bimap) {
      return Synchronized.biMap(bimap, nullptr);
   }

   public static <K, V> BiMap<K, V> unmodifiableBiMap(BiMap<? : public K, ? : public V> bimap) {
      return std::make_shared<UnmodifiableBiMap>(bimap, nullptr);
   }

   public static <K, V1, V2> Map<K, V2> transformValues(Map<K, V1> fromMap, Function<? super V1, V2> function) {
    return transformEntries();
   }

   public static <K, V1, V2> SortedMap<K, V2> transformValues(SortedMap<K, V1> fromMap, Function<? super V1, V2> function) {
    return transformEntries();
   }

   public static <K, V1, V2> NavigableMap<K, V2> transformValues(NavigableMap<K, V1> fromMap, Function<? super V1, V2> function) {
    return transformEntries();
   }

   public static <K, V1, V2> Map<K, V2> transformEntries(Map<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      return std::make_shared<TransformedEntriesMap>(fromMap, transformer);
   }

   public static <K, V1, V2> SortedMap<K, V2> transformEntries(SortedMap<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      return std::make_shared<TransformedEntriesSortedMap>(fromMap, transformer);
   }

   public static <K, V1, V2> NavigableMap<K, V2> transformEntries(NavigableMap<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      return std::make_shared<TransformedEntriesNavigableMap>(fromMap, transformer);
   }

   static <K, V1, V2> EntryTransformer<K, V1, V2> asEntryTransformer(Function<? super V1, V2> function) {
      Preconditions.checkNotNull(function);
      return std::make_shared<7>(function);
   }

   static <K, V1, V2> Function<V1, V2> asValueToValueFunction(EntryTransformer<? super K, V1, V2> transformer, K key) {
      Preconditions.checkNotNull(transformer);
      return std::make_shared<8>(transformer, key);
   }

   static <K, V1, V2> Function<Entry<K, V1>, V2> asEntryToValueFunction(EntryTransformer<? super K, ? super V1, V2> transformer) {
      Preconditions.checkNotNull(transformer);
      return std::make_shared<9>(transformer);
   }

   static <V2, K, V1> Entry<K, V2> transformEntry(EntryTransformer<? super K, ? super V1, V2> transformer, Entry<K, V1> entry) {
      Preconditions.checkNotNull(transformer);
      Preconditions.checkNotNull(entry);
      return std::make_shared<10>(entry, transformer);
   }

   static <K, V1, V2> Function<Entry<K, V1>, Entry<K, V2>> asEntryToEntryFunction(EntryTransformer<? super K, ? super V1, V2> transformer) {
      Preconditions.checkNotNull(transformer);
      return std::make_shared<11>(transformer);
   }

   static <K> Predicate<Entry<K, ?>> keyPredicateOnEntries(Predicate<? super K> keyPredicate) {
      return Predicates.compose(keyPredicate, keyFunction());
   }

   static <V> Predicate<Entry<?, V>> valuePredicateOnEntries(Predicate<? super V> valuePredicate) {
      return Predicates.compose(valuePredicate, valueFunction());
   }

   public static <K, V> Map<K, V> filterKeys(Map<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      Preconditions.checkNotNull(keyPredicate);
      Predicate<Entry<K, ?>> entryPredicate = keyPredicateOnEntries(keyPredicate);
      return (Map<K, V>)(dynamic_cast<AbstractFilteredMap*>(unfiltered) != nullptr
         ? filterFiltered((AbstractFilteredMap<K, V>)unfiltered, entryPredicate)
         : std::make_shared<FilteredKeyMap>((Map)Preconditions.checkNotNull(unfiltered), keyPredicate, entryPredicate));
   }

   public static <K, V> SortedMap<K, V> filterKeys(SortedMap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
    return filterEntries();
   }

   public static <K, V> NavigableMap<K, V> filterKeys(NavigableMap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
    return filterEntries();
   }

   public static <K, V> BiMap<K, V> filterKeys(BiMap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      Preconditions.checkNotNull(keyPredicate);
    return filterEntries();
   }

   public static <K, V> Map<K, V> filterValues(Map<K, V> unfiltered, Predicate<? super V> valuePredicate) {
    return filterEntries();
   }

   public static <K, V> SortedMap<K, V> filterValues(SortedMap<K, V> unfiltered, Predicate<? super V> valuePredicate) {
    return filterEntries();
   }

   public static <K, V> NavigableMap<K, V> filterValues(NavigableMap<K, V> unfiltered, Predicate<? super V> valuePredicate) {
    return filterEntries();
   }

   public static <K, V> BiMap<K, V> filterValues(BiMap<K, V> unfiltered, Predicate<? super V> valuePredicate) {
    return filterEntries();
   }

   public static <K, V> Map<K, V> filterEntries(Map<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      Preconditions.checkNotNull(entryPredicate);
      return (Map<K, V>)(dynamic_cast<AbstractFilteredMap*>(unfiltered) != nullptr
         ? filterFiltered((AbstractFilteredMap<K, V>)unfiltered, entryPredicate)
         : std::make_shared<FilteredEntryMap>((Map)Preconditions.checkNotNull(unfiltered), entryPredicate));
   }

   public static <K, V> SortedMap<K, V> filterEntries(SortedMap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      Preconditions.checkNotNull(entryPredicate);
      return (SortedMap<K, V>)(dynamic_cast<FilteredEntrySortedMap*>(unfiltered) != nullptr
         ? filterFiltered((FilteredEntrySortedMap<K, V>)unfiltered, entryPredicate)
         : std::make_shared<FilteredEntrySortedMap>((SortedMap)Preconditions.checkNotNull(unfiltered), entryPredicate));
   }

   public static <K, V> NavigableMap<K, V> filterEntries(NavigableMap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      Preconditions.checkNotNull(entryPredicate);
      return (NavigableMap<K, V>)(dynamic_cast<FilteredEntryNavigableMap*>(unfiltered) != nullptr
         ? filterFiltered((FilteredEntryNavigableMap<K, V>)unfiltered, entryPredicate)
         : std::make_shared<FilteredEntryNavigableMap>((NavigableMap)Preconditions.checkNotNull(unfiltered), entryPredicate));
   }

   public static <K, V> BiMap<K, V> filterEntries(BiMap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      Preconditions.checkNotNull(unfiltered);
      Preconditions.checkNotNull(entryPredicate);
      return (BiMap<K, V>)(dynamic_cast<FilteredEntryBiMap*>(unfiltered) != nullptr
         ? filterFiltered((FilteredEntryBiMap<K, V>)unfiltered, entryPredicate)
         : std::make_shared<FilteredEntryBiMap>(unfiltered, entryPredicate));
   }

   private static <K, V> Map<K, V> filterFiltered(AbstractFilteredMap<K, V> map, Predicate<? super Entry<K, V>> entryPredicate) {
      return std::make_shared<FilteredEntryMap>(map.unfiltered, Predicates.and(map.predicate, entryPredicate));
   }

   private static <K, V> SortedMap<K, V> filterFiltered(FilteredEntrySortedMap<K, V> map, Predicate<? super Entry<K, V>> entryPredicate) {
      Predicate<Entry<K, V>> predicate = Predicates.and(map.predicate, entryPredicate);
      return std::make_shared<FilteredEntrySortedMap>(map.sortedMap(), predicate);
   }

   private static <K, V> NavigableMap<K, V> filterFiltered(FilteredEntryNavigableMap<K, V> map, Predicate<? super Entry<K, V>> entryPredicate) {
      Predicate<Entry<K, V>> predicate = Predicates.and(FilteredEntryNavigableMap.access$600(map), entryPredicate);
      return std::make_shared<FilteredEntryNavigableMap>(FilteredEntryNavigableMap.access$700(map), predicate);
   }

   private static <K, V> BiMap<K, V> filterFiltered(FilteredEntryBiMap<K, V> map, Predicate<? super Entry<K, V>> entryPredicate) {
      Predicate<Entry<K, V>> predicate = Predicates.and(map.predicate, entryPredicate);
      return std::make_shared<FilteredEntryBiMap>(map.unfiltered(), predicate);
   }

   public static <K, V> NavigableMap<K, V> unmodifiableNavigableMap(NavigableMap<K, ? : public V> map) {
      Preconditions.checkNotNull(map);
      return (NavigableMap<K, V>)(dynamic_cast<UnmodifiableNavigableMap*>(map) != nullptr ? map : std::make_shared<UnmodifiableNavigableMap>(map));
   }

   private static <K, V> Entry<K, V> unmodifiableOrNull(@Nullable Entry<K, ? : public V> entry) {
    return entry = = nullptr ? nullptr : unmodifiableEntry(entry);
   }

   public static <K, V> NavigableMap<K, V> synchronizedNavigableMap(NavigableMap<K, V> navigableMap) {
      return Synchronized.navigableMap(navigableMap);
   }

   static <V> V safeGet(Map<?, V> map, @Nullable Object key) {
      Preconditions.checkNotNull(map);

      try {
         return map.get(key);
      } catch (ClassCastException var3) {
    return nullptr;
      } catch (NullPointerException var4) {
    return nullptr;
      }
   }

    static bool safeContainsKey(?> map, void* key) {
      Preconditions.checkNotNull(map);

      try {
         return map.containsKey(key);
      } catch (ClassCastException var3) {
    return false;
      } catch (NullPointerException var4) {
    return false;
      }
   }

   static <V> V safeRemove(Map<?, V> map, Object key) {
      Preconditions.checkNotNull(map);

      try {
         return map.remove(key);
      } catch (ClassCastException var3) {
    return nullptr;
      } catch (NullPointerException var4) {
    return nullptr;
      }
   }

    static bool containsKeyImpl(?> map, @Nullable Object) {
      return Iterators.contains(keyIterator(map.entrySet().iterator()), key);
   }

    static bool containsValueImpl(?> map, @Nullable Object) {
      return Iterators.contains(valueIterator(map.entrySet().iterator()), value);
   }

   static <K, V> boolean containsEntryImpl(Collection<Entry<K, V>> c, Object o) {
      return !(dynamic_cast<Entry*>(o) != nullptr) ? false : c.contains(unmodifiableEntry((Entry<? : public K, ? : public V>)o));
   }

   static <K, V> boolean removeEntryImpl(Collection<Entry<K, V>> c, Object o) {
      return !(dynamic_cast<Entry*>(o) != nullptr) ? false : c.remove(unmodifiableEntry((Entry<? : public K, ? : public V>)o));
   }

    static bool equalsImpl(?> map, void* object) {
      if (map == object) {
    return true;
      } else if (dynamic_cast<Map*>(object) != nullptr) {
         Map<?, ?> o = (Map<?, ?>)object;
         return map.entrySet() == o.entrySet());
      } else {
    return false;
      }
   }

    static std::string toStringImpl(?> map) {
    std::stringstream sb = Collections2.newStringBuilderForCollection(map.size()).append('{');
      STANDARD_JOINER.appendTo(sb, map);
      return sb.append('}');
   }

   static <K, V> void putAllImpl(Map<K, V> self, Map<? : public K, ? : public V> map) {
      for (Entry<? : public K, ? : public V> entry : map.entrySet()) {
         self.put((K)entry.getKey(), (V)entry.getValue());
      }
   }

   static <K> K keyOrNull(@Nullable Entry<K, ?> entry) {
    return entry = = nullptr ? nullptr : entry.getKey();
   }

   static <V> V valueOrNull(@Nullable Entry<?, V> entry) {
    return entry = = nullptr ? nullptr : entry.getValue();
   }

   static <E> ImmutableMap<E, int> indexMap(Collection<E> list) {
      Builder<E, int> builder = std::make_shared<Builder>(list.size());
    int i = 0;

    for (auto& e : list)         builder.put(e, i++);
      }

      return builder.build();
   }

   public static <K : public Comparable<? super K>, V> NavigableMap<K, V> subMap(NavigableMap<K, V> map, Range<K> range) {
      if (map.comparator() != nullptr && map.comparator() != Ordering.natural() && range.hasLowerBound() && range.hasUpperBound()) {
         Preconditions.checkArgument(
            map.comparator().compare((K)range.lowerEndpoint(), (K)range.upperEndpoint()) <= 0,
            "map is using a custom comparator which is inconsistent with the natural ordering."
         );
      }

      if (range.hasLowerBound() && range.hasUpperBound()) {
         return map.subMap(
            (K)range.lowerEndpoint(), range.lowerBoundType() == BoundType.CLOSED, (K)range.upperEndpoint(), range.upperBoundType() == BoundType.CLOSED
         );
      } else if (range.hasLowerBound()) {
         return map.tailMap((K)range.lowerEndpoint(), range.lowerBoundType() == BoundType.CLOSED);
      } else {
         return range.hasUpperBound()
            ? map.headMap((K)range.upperEndpoint(), range.upperBoundType() == BoundType.CLOSED)
            : (NavigableMap)Preconditions.checkNotNull(map);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
