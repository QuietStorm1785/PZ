#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/FilteredEntryMultimap/Keys/1.h"
#include "com/google/common/collect/Multimaps/Keys.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$Keys(FilteredEntryMultimap var1) {
      super(var1);
      this.this$0 = var1;
   }

    int remove(@Nullable Object, int occurrences) {
      CollectPreconditions.checkNonnegative(occurrences, "occurrences");
      if (occurrences == 0) {
         return this.count(key);
      } else {
         Collection<V> collection = (Collection<V>)this.this$0.unfiltered.asMap().get(key);
         if (collection == nullptr) {
    return 0;
         } else {
    K k = (K)key;
    int oldCount = 0;
            Iterator<V> itr = collection.iterator();

            while (itr.hasNext()) {
    V v = (V)itr.next();
               if (FilteredEntryMultimap.access$000(this.this$0, k, v)) {
                  if (++oldCount <= occurrences) {
                     itr.remove();
                  }
               }
            }

    return oldCount;
         }
      }
   }

   public Set<Entry<K>> entrySet() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
