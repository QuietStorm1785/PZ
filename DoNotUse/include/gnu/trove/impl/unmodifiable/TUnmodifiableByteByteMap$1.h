#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TByteByteIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteByteMap {
public:
    TByteByteIterator iter;

   TUnmodifiableByteByteMap$1(TUnmodifiableByteByteMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableByteByteMap.access$000(this.this$0).iterator();
   }

    uint8_t key() {
      return this.iter.key();
   }

    uint8_t value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    uint8_t setValue(uint8_t val) {
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
