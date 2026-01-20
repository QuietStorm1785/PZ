#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "com/google/common/collect/StandardTable/Column/EntrySet.h"
#include "com/google/common/collect/StandardTable/Column/KeySet.h"
#include "com/google/common/collect/StandardTable/Column/Values.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
    const C columnKey;

   StandardTable$Column(C var1, Object columnKey) {
      this.this$0 = var1;
      this.columnKey = (C)Preconditions.checkNotNull(columnKey);
   }

    V put(R key, V value) {
      return (V)this.this$0.put(key, this.columnKey, value);
   }

    V get(void* key) {
      return (V)this.this$0.get(key, this.columnKey);
   }

    bool containsKey(void* key) {
      return this.this$0.contains(key, this.columnKey);
   }

    V remove(void* key) {
      return (V)this.this$0.remove(key, this.columnKey);
   }

    bool removeFromColumnIf(Predicate<? super, V>> predicate) {
    bool changed = false;
      Iterator<Entry<R, Map<C, V>>> iterator = this.this$0.backingMap.entrySet().iterator();

      while (iterator.hasNext()) {
         Entry<R, Map<C, V>> entry = (Entry<R, Map<C, V>>)iterator.next();
         Map<C, V> map = (Map<C, V>)entry.getValue();
    V value = (V)map.get(this.columnKey);
         if (value != nullptr && predicate.apply(Maps.immutableEntry(entry.getKey(), value))) {
            map.remove(this.columnKey);
            changed = true;
            if (map.empty()) {
               iterator.remove();
            }
         }
      }

    return changed;
   }

   Set<Entry<R, V>> createEntrySet() {
      return std::make_shared<EntrySet>(this, nullptr);
   }

   Set<R> createKeySet() {
      return std::make_shared<KeySet>(this);
   }

   Collection<V> createValues() {
      return std::make_shared<Values>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
