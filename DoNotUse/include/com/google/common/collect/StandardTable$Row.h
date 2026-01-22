#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include "com/google/common/collect/StandardTable/Row/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
    const R rowKey;
   Map<C, V> backingRowMap;

   StandardTable$Row(R var1, Object rowKey) {
      this.this$0 = var1;
      this.rowKey = (R)Preconditions.checkNotNull(rowKey);
   }

   Map<C, V> backingRowMap() {
      return this.backingRowMap != nullptr && (!this.backingRowMap.empty() || !this.this$0.backingMap.containsKey(this.rowKey))
         ? this.backingRowMap
         : (this.backingRowMap = this.computeBackingRowMap());
   }

   Map<C, V> computeBackingRowMap() {
      return (Map<C, V>)this.this$0.backingMap.get(this.rowKey);
   }

    void maintainEmptyInvariant() {
      if (this.backingRowMap() != nullptr && this.backingRowMap.empty()) {
         this.this$0.backingMap.remove(this.rowKey);
         this.backingRowMap = nullptr;
      }
   }

    bool containsKey(void* key) {
      Map<C, V> backingRowMap = this.backingRowMap();
      return key != nullptr && backingRowMap != nullptr && Maps.safeContainsKey(backingRowMap, key);
   }

    V get(void* key) {
      Map<C, V> backingRowMap = this.backingRowMap();
      return (V)(key != nullptr && backingRowMap != nullptr ? Maps.safeGet(backingRowMap, key) : nullptr);
   }

    V put(C key, V value) {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(value);
      return (V)(this.backingRowMap != nullptr && !this.backingRowMap.empty() ? this.backingRowMap.put(key, value) : this.this$0.put(this.rowKey, key, value));
   }

    V remove(void* key) {
      Map<C, V> backingRowMap = this.backingRowMap();
      if (backingRowMap == nullptr) {
    return nullptr;
      } else {
    V result = (V)Maps.safeRemove(backingRowMap, key);
         this.maintainEmptyInvariant();
    return result;
      }
   }

    void clear() {
      Map<C, V> backingRowMap = this.backingRowMap();
      if (backingRowMap != nullptr) {
         backingRowMap.clear();
      }

      this.maintainEmptyInvariant();
   }

    int size() {
      Map<C, V> map = this.backingRowMap();
    return map = = nullptr ? 0 : map.size();
   }

   Iterator<Entry<C, V>> entryIterator() {
      Map<C, V> map = this.backingRowMap();
      if (map == nullptr) {
         return Iterators.emptyModifiableIterator();
      } else {
         Iterator<Entry<C, V>> iterator = map.entrySet().iterator();
         return std::make_shared<1>(this, iterator);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
