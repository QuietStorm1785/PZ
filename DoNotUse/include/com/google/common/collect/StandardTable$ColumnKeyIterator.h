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


class StandardTable {
public:
   const Map<C, V> seen;
   const Iterator<Map<C, V>> mapIterator;
   Iterator<Entry<C, V>> entryIterator;

   private StandardTable$ColumnKeyIterator(StandardTable var1) {
      this.this$0 = var1;
      this.seen = (Map<C, V>)this.this$0.factory.get();
      this.mapIterator = this.this$0.backingMap.values().iterator();
      this.entryIterator = Iterators.emptyIterator();
   }

    C computeNext() {
      while (true) {
         if (this.entryIterator.hasNext()) {
            Entry<C, V> entry = (Entry<C, V>)this.entryIterator.next();
            if (!this.seen.containsKey(entry.getKey())) {
               this.seen.put(entry.getKey(), entry.getValue());
               return (C)entry.getKey();
            }
         } else {
            if (!this.mapIterator.hasNext()) {
               return (C)this.endOfData();
            }

            this.entryIterator = ((Map)this.mapIterator.next()).entrySet().iterator();
         }
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
