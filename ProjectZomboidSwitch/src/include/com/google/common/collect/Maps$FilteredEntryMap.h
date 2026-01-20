#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/AbstractFilteredMap.h"
#include "com/google/common/collect/Maps/FilteredEntryMap/EntrySet.h"
#include "com/google/common/collect/Maps/FilteredEntryMap/KeySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Set<Entry<K, V>> filteredEntrySet;

   Maps$FilteredEntryMap(Map<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      super(unfiltered, entryPredicate);
      this.filteredEntrySet = Sets.filter(unfiltered.entrySet(), this.predicate);
   }

   protected Set<Entry<K, V>> createEntrySet() {
      return std::make_shared<EntrySet>(this, nullptr);
   }

   Set<K> createKeySet() {
      return std::make_shared<KeySet>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
