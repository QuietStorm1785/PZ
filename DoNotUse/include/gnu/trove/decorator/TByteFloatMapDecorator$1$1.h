#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TByteFloatMapDecorator/1.h"
#include "gnu/trove/iterator/TByteFloatIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TByteFloatMapDecorator {
public:
    const TByteFloatIterator it;

   TByteFloatMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<uint8_t, float> next() {
      this.it.advance();
    uint8_t ik = this.it.key();
    uint8_t key = ik == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(ik);
    float iv = this.it.value();
    float v = iv == this.this$1.this$0._map.getNoEntryValue() ? nullptr : this.this$1.this$0.wrapValue(iv);
      return new gnu.trove.decorator.TByteFloatMapDecorator.1.1.1(this, v, key);
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
