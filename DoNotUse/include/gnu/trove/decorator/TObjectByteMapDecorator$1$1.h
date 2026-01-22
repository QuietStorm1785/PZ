#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectByteMapDecorator/1.h"
#include "gnu/trove/iterator/TObjectByteIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectByteMapDecorator {
public:
   private const TObjectByteIterator<K> it;

   TObjectByteMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<K, uint8_t> next() {
      this.it.advance();
    K key = (K)this.it.key();
    uint8_t v = this.this$1.this$0.wrapValue(this.it.value());
      return new gnu.trove.decorator.TObjectByteMapDecorator.1.1.1(this, v, key);
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
