#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/common/collect/Maps/KeySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntryMap$KeySet(FilteredEntryMap var1) {
      super(var1);
      this.this$0 = var1;
   }

    bool remove(void* o) {
      if (this.this$0.containsKey(o)) {
         this.this$0.unfiltered.remove(o);
    return true;
      } else {
    return false;
      }
   }

    bool removeIf(Predicate<? super) {
      return Iterables.removeIf(this.this$0.unfiltered.entrySet(), Predicates.and(this.this$0.predicate, Maps.keyPredicateOnEntries(keyPredicate)));
   }

    bool removeAll(Collection<?> c) {
      return this.removeIf(Predicates.in(c));
   }

    bool retainAll(Collection<?> c) {
      return this.removeIf(Predicates.not(Predicates.in(c)));
   }

   public Object[] toArray() {
      return Lists.newArrayList(this.iterator()).toArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])Lists.newArrayList(this.iterator()).toArray(array);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
