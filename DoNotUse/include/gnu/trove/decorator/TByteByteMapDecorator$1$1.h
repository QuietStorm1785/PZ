#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TByteByteMapDecorator/1.h"
#include "gnu/trove/iterator/TByteByteIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TByteByteMapDecorator {
public:
    const TByteByteIterator it;

   TByteByteMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<uint8_t, uint8_t> next() {
      this.it.advance();
    uint8_t ik = this.it.key();
    uint8_t key = ik == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(ik);
    uint8_t iv = this.it.value();
    uint8_t v = iv == this.this$1.this$0._map.getNoEntryValue() ? nullptr : this.this$1.this$0.wrapValue(iv);
      return new gnu.trove.decorator.TByteByteMapDecorator.1.1.1(this, v, key);
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
