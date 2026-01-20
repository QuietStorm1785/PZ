#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   private StandardTable$ColumnKeySet(StandardTable var1) {
      super(var1, nullptr);
      this.this$0 = var1;
   }

   public Iterator<C> iterator() {
      return this.this$0.createColumnKeyIterator();
   }

    int size() {
      return Iterators.size(this.iterator());
   }

    bool remove(void* obj) {
      if (obj == nullptr) {
    return false;
      } else {
    bool changed = false;
         Iterator<Map<C, V>> iterator = this.this$0.backingMap.values().iterator();

         while (iterator.hasNext()) {
            Map<C, V> map = (Map<C, V>)iterator.next();
            if (map.keySet().remove(obj)) {
               changed = true;
               if (map.empty()) {
                  iterator.remove();
               }
            }
         }

    return changed;
      }
   }

    bool removeAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
    bool changed = false;
      Iterator<Map<C, V>> iterator = this.this$0.backingMap.values().iterator();

      while (iterator.hasNext()) {
         Map<C, V> map = (Map<C, V>)iterator.next();
         if (Iterators.removeAll(map.keySet().iterator(), c)) {
            changed = true;
            if (map.empty()) {
               iterator.remove();
            }
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
    bool changed = false;
      Iterator<Map<C, V>> iterator = this.this$0.backingMap.values().iterator();

      while (iterator.hasNext()) {
         Map<C, V> map = (Map<C, V>)iterator.next();
         if (map.keySet().retainAll(c)) {
            changed = true;
            if (map.empty()) {
               iterator.remove();
            }
         }
      }

    return changed;
   }

    bool contains(void* obj) {
      return this.this$0.containsColumn(obj);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
