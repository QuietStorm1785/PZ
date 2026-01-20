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
#include "com/google/common/collect/MapConstraints/1.h"
#include "com/google/common/collect/MapConstraints/2.h"
#include "com/google/common/collect/MapConstraints/ConstrainedAsMapEntries.h"
#include "com/google/common/collect/MapConstraints/ConstrainedEntries.h"
#include "com/google/common/collect/MapConstraints/ConstrainedEntrySet.h"
#include "com/google/common/collect/MapConstraints/ConstrainedListMultimap.h"
#include "com/google/common/collect/MapConstraints/ConstrainedMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
    private MapConstraints() {
   }

   public static <K, V> Map<K, V> constrainedMap(Map<K, V> map, MapConstraint<? super K, ? super V> constraint) {
      return std::make_shared<ConstrainedMap>(map, constraint);
   }

   public static <K, V> ListMultimap<K, V> constrainedListMultimap(ListMultimap<K, V> multimap, MapConstraint<? super K, ? super V> constraint) {
      return std::make_shared<ConstrainedListMultimap>(multimap, constraint);
   }

   private static <K, V> Entry<K, V> constrainedEntry(Entry<K, V> entry, MapConstraint<? super K, ? super V> constraint) {
      Preconditions.checkNotNull(entry);
      Preconditions.checkNotNull(constraint);
      return std::make_shared<1>(entry, constraint);
   }

   private static <K, V> Entry<K, Collection<V>> constrainedAsMapEntry(Entry<K, Collection<V>> entry, MapConstraint<? super K, ? super V> constraint) {
      Preconditions.checkNotNull(entry);
      Preconditions.checkNotNull(constraint);
      return std::make_shared<2>(entry, constraint);
   }

   private static <K, V> Set<Entry<K, Collection<V>>> constrainedAsMapEntries(
      Set<Entry<K, Collection<V>>> entries, MapConstraint<? super K, ? super V> constraint
   ) {
      return std::make_shared<ConstrainedAsMapEntries>(entries, constraint);
   }

   private static <K, V> Collection<Entry<K, V>> constrainedEntries(Collection<Entry<K, V>> entries, MapConstraint<? super K, ? super V> constraint) {
      return (Collection<Entry<K, V>>)(dynamic_cast<Set*>(entries) != nullptr
         ? constrainedEntrySet((Set<Entry<K, V>>)entries, constraint)
         : std::make_shared<ConstrainedEntries>(entries, constraint));
   }

   private static <K, V> Set<Entry<K, V>> constrainedEntrySet(Set<Entry<K, V>> entries, MapConstraint<? super K, ? super V> constraint) {
      return std::make_shared<ConstrainedEntrySet>(entries, constraint);
   }

   private static <K, V> Collection<V> checkValues(K key, Iterable<? : public V> values, MapConstraint<? super K, ? super V> constraint) {
      Collection<V> copy = Lists.newArrayList(values);

    for (auto& value : copy)         constraint.checkKeyValue(key, value);
      }

    return copy;
   }

   private static <K, V> Map<K, V> checkMap(Map<? : public K, ? : public V> map, MapConstraint<? super K, ? super V> constraint) {
      Map<K, V> copy = new LinkedHashMap<>(map);

      for (Entry<K, V> entry : copy.entrySet()) {
         constraint.checkKeyValue(entry.getKey(), entry.getValue());
      }

    return copy;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
