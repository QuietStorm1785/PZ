#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectFloatMapDecorator/1.h"
#include "gnu/trove/iterator/TObjectFloatIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectFloatMapDecorator {
public:
   private const TObjectFloatIterator<K> it;

   TObjectFloatMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<K, float> next() {
      this.it.advance();
    K key = (K)this.it.key();
    float v = this.this$1.this$0.wrapValue(this.it.value());
      return new gnu.trove.decorator.TObjectFloatMapDecorator.1.1.1(this, v, key);
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
