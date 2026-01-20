#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TFloatDoubleIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatDoubleMap {
public:
    TFloatDoubleIterator iter;

   TUnmodifiableFloatDoubleMap$1(TUnmodifiableFloatDoubleMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableFloatDoubleMap.access$000(this.this$0).iterator();
   }

    float key() {
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
