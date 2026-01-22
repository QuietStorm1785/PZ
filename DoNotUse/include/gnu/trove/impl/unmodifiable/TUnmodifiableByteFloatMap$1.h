#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TByteFloatIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteFloatMap {
public:
    TByteFloatIterator iter;

   TUnmodifiableByteFloatMap$1(TUnmodifiableByteFloatMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableByteFloatMap.access$000(this.this$0).iterator();
   }

    uint8_t key() {
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
