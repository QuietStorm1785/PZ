#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TShortObjectMapDecorator/1.h"
#include "gnu/trove/iterator/TShortObjectIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TShortObjectMapDecorator {
public:
   private const TShortObjectIterator<V> it;

   TShortObjectMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<int16_t, V> next() {
      this.it.advance();
    short k = this.it.key();
    short key = k == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(k);
    V v = (V)this.it.value();
      return new gnu.trove.decorator.TShortObjectMapDecorator.1.1.1(this, v, key);
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
