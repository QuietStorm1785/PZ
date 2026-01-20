#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TCharIterator.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TCharSetDecorator {
public:
    const TCharIterator it;

   TCharSetDecorator$1(TCharSetDecorator var1) {
      this.this$0 = var1;
      this.it = this.this$0._set.iterator();
   }

    char next() {
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
