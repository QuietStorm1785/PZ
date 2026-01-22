#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/common/collect/Maps/FilteredEntryMap/EntrySet/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private Maps$FilteredEntryMap$EntrySet(FilteredEntryMap var1) {
      this.this$0 = var1;
   }

   protected Set<Entry<K, V>> delegate() {
      return this.this$0.filteredEntrySet;
   }

   public Iterator<Entry<K, V>> iterator() {
      return std::make_shared<1>(this, this.this$0.filteredEntrySet.iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
