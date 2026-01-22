#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ConcurrentHashMultiset {
public:
   private const Iterator<Entry<E, AtomicInteger>> mapEntries;

   ConcurrentHashMultiset$2(ConcurrentHashMultiset var1) {
      this.this$0 = var1;
      this.mapEntries = ConcurrentHashMultiset.access$100(this.this$0).entrySet().iterator();
   }

   protected com.google.common.collect.Multiset.Entry<E> computeNext() {
      while (this.mapEntries.hasNext()) {
         Entry<E, AtomicInteger> mapEntry = (Entry<E, AtomicInteger>)this.mapEntries.next();
    int count = mapEntry.getValue().get();
         if (count != 0) {
            return Multisets.immutableEntry(mapEntry.getKey(), count);
         }
      }

      return (com.google.common.collect.Multiset.Entry<E>)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
