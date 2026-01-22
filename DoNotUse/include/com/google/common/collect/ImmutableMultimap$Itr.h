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


class ImmutableMultimap {
public:
   const Iterator<Entry<K, Collection<V>>> mapIterator;
    K key;
   Iterator<V> valueIterator;

   private ImmutableMultimap$Itr(ImmutableMultimap var1) {
      this.this$0 = var1;
      this.mapIterator = this.this$0.asMap().entrySet().iterator();
      this.key = nullptr;
      this.valueIterator = Iterators.emptyIterator();
   }

   abstract T output(K var1, V var2);

    bool hasNext() {
      return this.mapIterator.hasNext() || this.valueIterator.hasNext();
   }

    T next() {
      if (!this.valueIterator.hasNext()) {
         Entry<K, Collection<V>> mapEntry = (Entry<K, Collection<V>>)this.mapIterator.next();
         this.key = (K)mapEntry.getKey();
         this.valueIterator = ((Collection)mapEntry.getValue()).iterator();
      }

      return this.output(this.key, this.valueIterator.next());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
