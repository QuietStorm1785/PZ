#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/KeySet/1.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$KeySet(Map<K, Collection<V>> var1, Map subMap) {
      super(subMap);
      this.this$0 = var1;
   }

   public Iterator<K> iterator() {
      Iterator<Entry<K, Collection<V>>> entryIterator = this.map().entrySet().iterator();
      return std::make_shared<1>(this, entryIterator);
   }

    bool remove(void* key) {
    int count = 0;
      Collection<V> collection = (Collection<V>)this.map().remove(key);
      if (collection != nullptr) {
         count = collection.size();
         collection.clear();
         AbstractMapBasedMultimap.access$220(this.this$0, count);
      }

      return count > 0;
   }

    void clear() {
      Iterators.clear(this.iterator());
   }

    bool containsAll(Collection<?> c) {
      return this.map().keySet().containsAll(c);
   }

    bool equals(@Nullable Object) {
    return this = = object || this.map().keySet() == object);
   }

    int hashCode() {
      return this.map().keySet().hashCode();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
