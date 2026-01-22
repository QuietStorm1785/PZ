#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/FilteredEntryMultimap/AsMap/1EntrySetImpl.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap/1KeySetImpl.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap/1ValuesImpl.h"
#include "com/google/common/collect/FilteredEntryMultimap/ValuePredicate.h"
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$AsMap(FilteredEntryMultimap var1) {
      this.this$0 = var1;
   }

    bool containsKey(@Nullable Object) {
      return this.get(key) != nullptr;
   }

    void clear() {
      this.this$0.clear();
   }

   public Collection<V> get(@Nullable Object key) {
      Collection<V> result = (Collection<V>)this.this$0.unfiltered.asMap().get(key);
      if (result == nullptr) {
    return nullptr;
      } else {
         result = FilteredEntryMultimap.filterCollection(result, std::make_shared<ValuePredicate>(this.this$0, key));
         return result.empty() ? nullptr : result;
      }
   }

   public Collection<V> remove(@Nullable Object key) {
      Collection<V> collection = (Collection<V>)this.this$0.unfiltered.asMap().get(key);
      if (collection == nullptr) {
    return nullptr;
      } else {
    K k = (K)key;
         List<V> result = Lists.newArrayList();
         Iterator<V> itr = collection.iterator();

         while (itr.hasNext()) {
    V v = (V)itr.next();
            if (FilteredEntryMultimap.access$000(this.this$0, k, v)) {
               itr.remove();
               result.push_back(v);
            }
         }

         if (result.empty()) {
    return nullptr;
         } else {
            return (Collection<V>)(this.this$0.dynamic_cast<SetMultimap*>(unfiltered) != nullptr
               ? Collections.unmodifiableSet(Sets.newLinkedHashSet(result))
               : Collections.unmodifiableList(result));
         }
      }
   }

   Set<K> createKeySet() {
      return std::make_shared<1KeySetImpl>(this);
   }

   Set<Entry<K, Collection<V>>> createEntrySet() {
      return std::make_shared<1EntrySetImpl>(this);
   }

   Collection<Collection<V>> createValues() {
      return std::make_shared<1ValuesImpl>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
