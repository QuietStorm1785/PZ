#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedHashMultimap/ValueEntry.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSet.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSetLink.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedHashMultimap {
public:
   ValueSetLink<K, V> nextEntry;
   ValueEntry<K, V> toRemove;
    int expectedModCount;

   LinkedHashMultimap$ValueSet$1(ValueSet var1) {
      this.this$1 = var1;
      this.nextEntry = ValueSet.access$000(this.this$1);
      this.expectedModCount = ValueSet.access$100(this.this$1);
   }

    void checkForComodification() {
      if (ValueSet.access$100(this.this$1) != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      }
   }

    bool hasNext() {
      this.checkForComodification();
      return this.nextEntry != this.this$1;
   }

    V next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         ValueEntry<K, V> entry = (ValueEntry<K, V>)this.nextEntry;
    V result = (V)entry.getValue();
         this.toRemove = entry;
         this.nextEntry = entry.getSuccessorInValueSet();
    return result;
      }
   }

    void remove() {
      this.checkForComodification();
      CollectPreconditions.checkRemove(this.toRemove != nullptr);
      this.this$1.remove(this.toRemove.getValue());
      this.expectedModCount = ValueSet.access$100(this.this$1);
      this.toRemove = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
