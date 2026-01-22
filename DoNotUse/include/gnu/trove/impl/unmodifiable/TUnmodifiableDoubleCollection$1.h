#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TDoubleIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleCollection {
public:
    TDoubleIterator i;

   TUnmodifiableDoubleCollection$1(TUnmodifiableDoubleCollection var1) {
      this.this$0 = var1;
      this.i = this.this$0.c.iterator();
   }

    bool hasNext() {
      return this.i.hasNext();
   }

    double next() {
      return this.i.next();
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
