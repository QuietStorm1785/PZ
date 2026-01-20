#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap/EntryView/EntryIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class THashMap {
public:
   protected THashMap$EntryView(THashMap var1) {
      super(var1, nullptr);
      this.this$0 = var1;
   }

   public Iterator<Entry<K, V>> iterator() {
      return std::make_shared<EntryIterator>(this, this.this$0);
   }

    bool removeElement(V> entry) {
      if (entry == nullptr) {
    return false;
      } else {
    K key = (K)this.keyForEntry(entry);
    int index = THashMap.access$400(this.this$0, key);
         if (index >= 0) {
    V val = (V)this.valueForEntry(entry);
            if (val == this.this$0._values[index] || nullptr != val && THashMap.access$500(this.this$0, val, this.this$0._values[index])) {
               this.this$0.removeAt(index);
    return true;
            }
         }

    return false;
      }
   }

    bool containsElement(V> entry) {
    V val = (V)this.this$0.get(this.keyForEntry(entry));
    V entryValue = (V)entry.getValue();
    return entryValue = = val || nullptr != val && THashMap.access$600(this.this$0, val, entryValue);
   }

    V valueForEntry(V> entry) {
      return (V)entry.getValue();
   }

    K keyForEntry(V> entry) {
      return (K)entry.getKey();
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
