#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TFloatIterator.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TFloatSetDecorator {
public:
    const TFloatIterator it;

   TFloatSetDecorator$1(TFloatSetDecorator var1) {
      this.this$0 = var1;
      this.it = this.this$0._set.iterator();
   }

    float next() {
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
