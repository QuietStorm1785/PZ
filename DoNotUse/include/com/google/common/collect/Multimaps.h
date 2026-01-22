#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/ImmutableListMultimap/Builder.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Maps/UnmodifiableEntries.h"
#include "com/google/common/collect/Multimaps/CustomListMultimap.h"
#include "com/google/common/collect/Multimaps/CustomMultimap.h"
#include "com/google/common/collect/Multimaps/CustomSetMultimap.h"
#include "com/google/common/collect/Multimaps/CustomSortedSetMultimap.h"
#include "com/google/common/collect/Multimaps/MapMultimap.h"
#include "com/google/common/collect/Multimaps/TransformedEntriesListMultimap.h"
#include "com/google/common/collect/Multimaps/TransformedEntriesMultimap.h"
#include "com/google/common/collect/Multimaps/UnmodifiableListMultimap.h"
#include "com/google/common/collect/Multimaps/UnmodifiableMultimap.h"
#include "com/google/common/collect/Multimaps/UnmodifiableSetMultimap.h"
#include "com/google/common/collect/Multimaps/UnmodifiableSortedSetMultimap.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
    private Multimaps() {
   }

   public static <K, V> Multimap<K, V> newMultimap(Map<K, Collection<V>> map, Supplier<? : public Collection<V>> factory) {
      return std::make_shared<CustomMultimap>(map, factory);
   }

   public static <K, V> ListMultimap<K, V> newListMultimap(Map<K, Collection<V>> map, Supplier<? : public List<V>> factory) {
      return std::make_shared<CustomListMultimap>(map, factory);
   }

   public static <K, V> SetMultimap<K, V> newSetMultimap(Map<K, Collection<V>> map, Supplier<? : public Set<V>> factory) {
      return std::make_shared<CustomSetMultimap>(map, factory);
   }

   public static <K, V> SortedSetMultimap<K, V> newSortedSetMultimap(Map<K, Collection<V>> map, Supplier<? : public SortedSet<V>> factory) {
      return std::make_shared<CustomSortedSetMultimap>(map, factory);
   }

   public static <K, V, M : public Multimap<K, V>> M invertFrom(Multimap<? : public V, ? : public K> source, M dest) {
      Preconditions.checkNotNull(dest);

      for (Entry<? : public V, ? : public K> entry : source.entries()) {
         dest.put(entry.getValue(), entry.getKey());
      }

    return dest;
   }

   public static <K, V> Multimap<K, V> synchronizedMultimap(Multimap<K, V> multimap) {
      return Synchronized.multimap(multimap, nullptr);
   }

   public static <K, V> Multimap<K, V> unmodifiableMultimap(Multimap<K, V> delegate) {
      return (Multimap<K, V>)(!(dynamic_cast<UnmodifiableMultimap*>(delegate) != nullptr) && !(dynamic_cast<ImmutableMultimap*>(delegate) != nullptr)
         ? std::make_shared<UnmodifiableMultimap>(delegate)
         : delegate);
   }

   public static <K, V> Multimap<K, V> unmodifiableMultimap(ImmutableMultimap<K, V> delegate) {
      return (Multimap<K, V>)Preconditions.checkNotNull(delegate);
   }

   public static <K, V> SetMultimap<K, V> synchronizedSetMultimap(SetMultimap<K, V> multimap) {
      return Synchronized.setMultimap(multimap, nullptr);
   }

   public static <K, V> SetMultimap<K, V> unmodifiableSetMultimap(SetMultimap<K, V> delegate) {
      return (SetMultimap<K, V>)(!(dynamic_cast<UnmodifiableSetMultimap*>(delegate) != nullptr) && !(dynamic_cast<ImmutableSetMultimap*>(delegate) != nullptr)
         ? std::make_shared<UnmodifiableSetMultimap>(delegate)
         : delegate);
   }

   public static <K, V> SetMultimap<K, V> unmodifiableSetMultimap(ImmutableSetMultimap<K, V> delegate) {
      return (SetMultimap<K, V>)Preconditions.checkNotNull(delegate);
   }

   public static <K, V> SortedSetMultimap<K, V> synchronizedSortedSetMultimap(SortedSetMultimap<K, V> multimap) {
      return Synchronized.sortedSetMultimap(multimap, nullptr);
   }

   public static <K, V> SortedSetMultimap<K, V> unmodifiableSortedSetMultimap(SortedSetMultimap<K, V> delegate) {
      return (SortedSetMultimap<K, V>)(dynamic_cast<UnmodifiableSortedSetMultimap*>(delegate) != nullptr ? delegate : std::make_shared<UnmodifiableSortedSetMultimap>(delegate));
   }

   public static <K, V> ListMultimap<K, V> synchronizedListMultimap(ListMultimap<K, V> multimap) {
      return Synchronized.listMultimap(multimap, nullptr);
   }

   public static <K, V> ListMultimap<K, V> unmodifiableListMultimap(ListMultimap<K, V> delegate) {
      return (ListMultimap<K, V>)(!(dynamic_cast<UnmodifiableListMultimap*>(delegate) != nullptr) && !(dynamic_cast<ImmutableListMultimap*>(delegate) != nullptr)
         ? std::make_shared<UnmodifiableListMultimap>(delegate)
         : delegate);
   }

   public static <K, V> ListMultimap<K, V> unmodifiableListMultimap(ImmutableListMultimap<K, V> delegate) {
      return (ListMultimap<K, V>)Preconditions.checkNotNull(delegate);
   }

   private static <V> Collection<V> unmodifiableValueCollection(Collection<V> collection) {
      if (dynamic_cast<SortedSet*>(collection) != nullptr) {
         return Collections.unmodifiableSortedSet((SortedSet<V>)collection);
      } else if (dynamic_cast<Set*>(collection) != nullptr) {
         return Collections.unmodifiableSet((Set<? : public V>)collection);
      } else {
         return (Collection<V>)(dynamic_cast<List*>(collection) != nullptr
            ? Collections.unmodifiableList((List<? : public V>)collection)
            : Collections.unmodifiableCollection(collection));
      }
   }

   private static <K, V> Collection<Entry<K, V>> unmodifiableEntries(Collection<Entry<K, V>> entries) {
      return (Collection<Entry<K, V>>)(dynamic_cast<Set*>(entries) != nullptr
         ? Maps.unmodifiableEntrySet((Set)entries)
         : std::make_shared<UnmodifiableEntries>(Collections.unmodifiableCollection(entries)));
   }

   public static <K, V> Map<K, List<V>> asMap(ListMultimap<K, V> multimap) {
      return multimap.asMap();
   }

   public static <K, V> Map<K, Set<V>> asMap(SetMultimap<K, V> multimap) {
      return multimap.asMap();
   }

   public static <K, V> Map<K, SortedSet<V>> asMap(SortedSetMultimap<K, V> multimap) {
      return multimap.asMap();
   }

   public static <K, V> Map<K, Collection<V>> asMap(Multimap<K, V> multimap) {
      return multimap.asMap();
   }

   public static <K, V> SetMultimap<K, V> forMap(Map<K, V> map) {
      return std::make_shared<MapMultimap>(map);
   }

   public static <K, V1, V2> Multimap<K, V2> transformValues(Multimap<K, V1> fromMultimap, Function<? super V1, V2> function) {
      Preconditions.checkNotNull(function);
      EntryTransformer<K, V1, V2> transformer = Maps.asEntryTransformer(function);
    return transformEntries();
   }

   public static <K, V1, V2> Multimap<K, V2> transformEntries(Multimap<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      return std::make_shared<TransformedEntriesMultimap>(fromMap, transformer);
   }

   public static <K, V1, V2> ListMultimap<K, V2> transformValues(ListMultimap<K, V1> fromMultimap, Function<? super V1, V2> function) {
      Preconditions.checkNotNull(function);
      EntryTransformer<K, V1, V2> transformer = Maps.asEntryTransformer(function);
    return transformEntries();
   }

   public static <K, V1, V2> ListMultimap<K, V2> transformEntries(ListMultimap<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      return std::make_shared<TransformedEntriesListMultimap>(fromMap, transformer);
   }

   public static <K, V> ImmutableListMultimap<K, V> index(Iterable<V> values, Function<? super V, K> keyFunction) {
    return index();
   }

   public static <K, V> ImmutableListMultimap<K, V> index(Iterator<V> values, Function<? super V, K> keyFunction) {
      Preconditions.checkNotNull(keyFunction);
      Builder<K, V> builder = ImmutableListMultimap.builder();

      while (values.hasNext()) {
    V value = values.next();
         Preconditions.checkNotNull(value, values);
         builder.put(keyFunction.apply(value), value);
      }

      return builder.build();
   }

   public static <K, V> Multimap<K, V> filterKeys(Multimap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      if (dynamic_cast<SetMultimap*>(unfiltered) != nullptr) {
    return filterKeys();
      } else if (dynamic_cast<ListMultimap*>(unfiltered) != nullptr) {
    return filterKeys();
      } else if (dynamic_cast<FilteredKeyMultimap*>(unfiltered) != nullptr) {
         FilteredKeyMultimap<K, V> prev = (FilteredKeyMultimap<K, V>)unfiltered;
         return std::make_shared<FilteredKeyMultimap>(prev.unfiltered, Predicates.and(prev.keyPredicate, keyPredicate));
      } else if (dynamic_cast<FilteredMultimap*>(unfiltered) != nullptr) {
         FilteredMultimap<K, V> prev = (FilteredMultimap<K, V>)unfiltered;
    return filterFiltered();
      } else {
         return std::make_shared<FilteredKeyMultimap>(unfiltered, keyPredicate);
      }
   }

   public static <K, V> SetMultimap<K, V> filterKeys(SetMultimap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      if (dynamic_cast<FilteredKeySetMultimap*>(unfiltered) != nullptr) {
         FilteredKeySetMultimap<K, V> prev = (FilteredKeySetMultimap<K, V>)unfiltered;
         return std::make_shared<FilteredKeySetMultimap>(prev.unfiltered(), Predicates.and(prev.keyPredicate, keyPredicate));
      } else if (dynamic_cast<FilteredSetMultimap*>(unfiltered) != nullptr) {
         FilteredSetMultimap<K, V> prev = (FilteredSetMultimap<K, V>)unfiltered;
    return filterFiltered();
      } else {
         return std::make_shared<FilteredKeySetMultimap>(unfiltered, keyPredicate);
      }
   }

   public static <K, V> ListMultimap<K, V> filterKeys(ListMultimap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      if (dynamic_cast<FilteredKeyListMultimap*>(unfiltered) != nullptr) {
         FilteredKeyListMultimap<K, V> prev = (FilteredKeyListMultimap<K, V>)unfiltered;
         return std::make_shared<FilteredKeyListMultimap>(prev.unfiltered(), Predicates.and(prev.keyPredicate, keyPredicate));
      } else {
         return std::make_shared<FilteredKeyListMultimap>(unfiltered, keyPredicate);
      }
   }

   public static <K, V> Multimap<K, V> filterValues(Multimap<K, V> unfiltered, Predicate<? super V> valuePredicate) {
    return filterEntries();
   }

   public static <K, V> SetMultimap<K, V> filterValues(SetMultimap<K, V> unfiltered, Predicate<? super V> valuePredicate) {
    return filterEntries();
   }

   public static <K, V> Multimap<K, V> filterEntries(Multimap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      Preconditions.checkNotNull(entryPredicate);
      if (dynamic_cast<SetMultimap*>(unfiltered) != nullptr) {
    return filterEntries();
      } else {
         return (Multimap<K, V>)(dynamic_cast<FilteredMultimap*>(unfiltered) != nullptr
            ? filterFiltered((FilteredMultimap<K, V>)unfiltered, entryPredicate)
            : std::make_shared<FilteredEntryMultimap>((Multimap)Preconditions.checkNotNull(unfiltered), entryPredicate));
      }
   }

   public static <K, V> SetMultimap<K, V> filterEntries(SetMultimap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      Preconditions.checkNotNull(entryPredicate);
      return (SetMultimap<K, V>)(dynamic_cast<FilteredSetMultimap*>(unfiltered) != nullptr
         ? filterFiltered((FilteredSetMultimap<K, V>)unfiltered, entryPredicate)
         : std::make_shared<FilteredEntrySetMultimap>((SetMultimap)Preconditions.checkNotNull(unfiltered), entryPredicate));
   }

   private static <K, V> Multimap<K, V> filterFiltered(FilteredMultimap<K, V> multimap, Predicate<? super Entry<K, V>> entryPredicate) {
      Predicate<Entry<K, V>> predicate = Predicates.and(multimap.entryPredicate(), entryPredicate);
      return std::make_shared<FilteredEntryMultimap>(multimap.unfiltered(), predicate);
   }

   private static <K, V> SetMultimap<K, V> filterFiltered(FilteredSetMultimap<K, V> multimap, Predicate<? super Entry<K, V>> entryPredicate) {
      Predicate<Entry<K, V>> predicate = Predicates.and(multimap.entryPredicate(), entryPredicate);
      return std::make_shared<FilteredEntrySetMultimap>(multimap.unfiltered(), predicate);
   }

    static bool equalsImpl(?> multimap, @Nullable Object) {
      if (object == multimap) {
    return true;
      } else if (dynamic_cast<Multimap*>(object) != nullptr) {
         Multimap<?, ?> that = (Multimap<?, ?>)object;
         return multimap.asMap() == that.asMap());
      } else {
    return false;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
