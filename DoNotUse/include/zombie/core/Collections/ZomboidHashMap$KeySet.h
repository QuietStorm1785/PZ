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
   private ZomboidHashMap$KeySet(ZomboidHashMap var1) {
      this.this$0 = var1;
   }

   public Iterator<K> iterator() {
      return this.this$0.newKeyIterator();
   }

    int size() {
      return this.this$0.size;
   }

    bool contains(void* var1) {
      return this.this$0.containsKey(var1);
   }

    bool remove(void* var1) {
      return this.this$0.removeEntryForKey(var1) != nullptr;
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
