#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TLongDoubleIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongDoubleMap {
public:
    TLongDoubleIterator iter;

   TUnmodifiableLongDoubleMap$1(TUnmodifiableLongDoubleMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableLongDoubleMap.access$000(this.this$0).iterator();
   }

    long key() {
      return this.iter.key();
   }

    double value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    double setValue(double val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
