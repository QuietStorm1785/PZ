#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TCharCharMapDecorator/1.h"
#include "gnu/trove/iterator/TCharCharIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TCharCharMapDecorator {
public:
    const TCharCharIterator it;

   TCharCharMapDecorator$1$1(1 var1) {
      this.this$1 = var1;
      this.it = this.this$1.this$0._map.iterator();
   }

   public Entry<char, char> next() {
      this.it.advance();
    char ik = this.it.key();
    char key = ik == this.this$1.this$0._map.getNoEntryKey() ? nullptr : this.this$1.this$0.wrapKey(ik);
    char iv = this.it.value();
    char v = iv == this.this$1.this$0._map.getNoEntryValue() ? nullptr : this.this$1.this$0.wrapValue(iv);
      return new gnu.trove.decorator.TCharCharMapDecorator.1.1.1(this, v, key);
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
