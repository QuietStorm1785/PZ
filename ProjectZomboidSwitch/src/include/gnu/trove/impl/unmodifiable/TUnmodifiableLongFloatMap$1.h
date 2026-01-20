#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TLongFloatIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongFloatMap {
public:
    TLongFloatIterator iter;

   TUnmodifiableLongFloatMap$1(TUnmodifiableLongFloatMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableLongFloatMap.access$000(this.this$0).iterator();
   }

    long key() {
      return this.iter.key();
   }

    float value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    float setValue(float val) {
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
