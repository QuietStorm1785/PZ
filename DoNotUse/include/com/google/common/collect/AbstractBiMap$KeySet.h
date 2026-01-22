#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractBiMap {
public:
   private AbstractBiMap$KeySet(AbstractBiMap var1) {
      this.this$0 = var1;
   }

   protected Set<K> delegate() {
      return AbstractBiMap.access$100(this.this$0).keySet();
   }

    void clear() {
      this.this$0.clear();
   }

    bool remove(void* key) {
      if (!this.contains(key)) {
    return false;
      } else {
         AbstractBiMap.access$200(this.this$0, key);
    return true;
      }
   }

    bool removeAll(Collection<?> keysToRemove) {
      return this.standardRemoveAll(keysToRemove);
   }

    bool retainAll(Collection<?> keysToRetain) {
      return this.standardRetainAll(keysToRetain);
   }

   public Iterator<K> iterator() {
      return Maps.keyIterator(this.this$0.entrySet().iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
