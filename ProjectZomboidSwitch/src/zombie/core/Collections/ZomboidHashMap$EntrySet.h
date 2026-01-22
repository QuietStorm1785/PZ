#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidHashMap {
public:
   private ZomboidHashMap$EntrySet(ZomboidHashMap var1) {
      this.this$0 = var1;
   }

   public Iterator<Entry<K, V>> iterator() {
      return this.this$0.newEntryIterator();
   }

    bool contains(void* var1) {
      if (!(dynamic_cast<Entry*>(var1) != nullptr var2)) {
    return false;
      } else {
         zombie.core.Collections.ZomboidHashMap.Entry var3 = this.this$0.getEntry(var2.getKey());
         return var3 != nullptr && var3 == var2);
      }
   }

    bool remove(void* var1) {
      return this.this$0.removeMapping(var1) != nullptr;
   }

    int size() {
      return this.this$0.size;
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
