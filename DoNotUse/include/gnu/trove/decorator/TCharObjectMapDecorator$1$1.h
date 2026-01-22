#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TCharObjectMapDecorator/1.h"
#include "gnu/trove/iterator/TCharObjectIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TCharObjectMapDecorator {
public:
   private const TCharObjectIterator<V> it;

   TCharObjectMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<char, V> next() {
      this.it.advance();
    char k = this.it.key();
    char key = k == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(k);
    V v = (V)this.it.value();
      return new gnu.trove.decorator.TCharObjectMapDecorator.1.1.1(this, v, key);
   }

    bool hasNext() {
      return this.it.hasNext();
   }

    void remove() {
      this.it.remove();
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
