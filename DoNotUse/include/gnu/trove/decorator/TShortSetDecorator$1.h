#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortIterator.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TShortSetDecorator {
public:
    const TShortIterator it;

   TShortSetDecorator$1(TShortSetDecorator var1) {
      this.this$0 = var1;
      this.it = this.this$0._set.iterator();
   }

    short next() {
      return this.it.next();
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
