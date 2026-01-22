#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectIntMapDecorator/1.h"
#include "gnu/trove/iterator/TObjectIntIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectIntMapDecorator {
public:
   private const TObjectIntIterator<K> it;

   TObjectIntMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<K, int> next() {
      this.it.advance();
    K key = (K)this.it.key();
    int v = this.this$1.this$0.wrapValue(this.it.value());
      return new gnu.trove.decorator.TObjectIntMapDecorator.1.1.1(this, v, key);
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
