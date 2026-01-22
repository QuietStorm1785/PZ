#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TDoubleShortMapDecorator/1.h"
#include "gnu/trove/iterator/TDoubleShortIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TDoubleShortMapDecorator {
public:
    const TDoubleShortIterator it;

   TDoubleShortMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<double, int16_t> next() {
      this.it.advance();
    double ik = this.it.key();
    double key = ik == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(ik);
    short iv = this.it.value();
    short v = iv == this.this$1.this$0._map.getNoEntryValue() ? nullptr : this.this$1.this$0.wrapValue(iv);
      return new gnu.trove.decorator.TDoubleShortMapDecorator.1.1.1(this, v, key);
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
