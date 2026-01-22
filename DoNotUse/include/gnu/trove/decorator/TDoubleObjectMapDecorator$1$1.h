#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TDoubleObjectMapDecorator/1.h"
#include "gnu/trove/iterator/TDoubleObjectIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TDoubleObjectMapDecorator {
public:
   private const TDoubleObjectIterator<V> it;

   TDoubleObjectMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<double, V> next() {
      this.it.advance();
    double k = this.it.key();
    double key = k == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(k);
    V v = (V)this.it.value();
      return new gnu.trove.decorator.TDoubleObjectMapDecorator.1.1.1(this, v, key);
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
