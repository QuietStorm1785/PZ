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


class AbstractMapBasedMultimap {
public:
   const Iterator<Entry<K, Collection<V>>> keyIterator;
    K key;
   Collection<V> collection;
   Iterator<V> valueIterator;

   AbstractMapBasedMultimap$Itr(AbstractMapBasedMultimap var1) {
      this.this$0 = var1;
      this.keyIterator = AbstractMapBasedMultimap.access$000(var1).entrySet().iterator();
      this.key = nullptr;
      this.collection = nullptr;
      this.valueIterator = Iterators.emptyModifiableIterator();
   }

   abstract T output(K var1, V var2);

    bool hasNext() {
      return this.keyIterator.hasNext() || this.valueIterator.hasNext();
   }

    T next() {
      if (!this.valueIterator.hasNext()) {
         Entry<K, Collection<V>> mapEntry = (Entry<K, Collection<V>>)this.keyIterator.next();
         this.key = (K)mapEntry.getKey();
         this.collection = (Collection<V>)mapEntry.getValue();
         this.valueIterator = this.collection.iterator();
      }

      return this.output(this.key, this.valueIterator.next());
   }

    void remove() {
      this.valueIterator.remove();
      if (this.collection.empty()) {
         this.keyIterator.remove();
      }

      AbstractMapBasedMultimap.access$210(this.this$0);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
