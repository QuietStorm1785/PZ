#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include "com/google/common/collect/StandardTable/Column.h"
#include "com/google/common/collect/StandardTable/Column/EntrySetIterator.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   private StandardTable$Column$EntrySet(Column var1) {
      this.this$1 = var1;
   }

   public Iterator<Entry<R, V>> iterator() {
      return std::make_shared<EntrySetIterator>(this.this$1, nullptr);
   }

    int size() {
    int size = 0;

      for (Map<C, V> map : this.this$1.this$0.backingMap.values()) {
         if (map.containsKey(this.this$1.columnKey)) {
            size++;
         }
      }

    return size;
   }

    bool isEmpty() {
      return !this.this$1.this$0.containsColumn(this.this$1.columnKey);
   }

    void clear() {
      this.this$1.removeFromColumnIf(Predicates.alwaysTrue());
   }

    bool contains(void* o) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         return StandardTable.access$300(this.this$1.this$0, entry.getKey(), this.this$1.columnKey, entry.getValue());
      } else {
    return false;
      }
   }

    bool remove(void* obj) {
      if (dynamic_cast<Entry*>(obj) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)obj;
         return StandardTable.access$400(this.this$1.this$0, entry.getKey(), this.this$1.columnKey, entry.getValue());
      } else {
    return false;
      }
   }

    bool retainAll(Collection<?> c) {
      return this.this$1.removeFromColumnIf(Predicates.not(Predicates.in(c)));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
