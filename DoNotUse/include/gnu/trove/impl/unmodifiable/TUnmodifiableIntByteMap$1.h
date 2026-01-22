#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TIntByteIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntByteMap {
public:
    TIntByteIterator iter;

   TUnmodifiableIntByteMap$1(TUnmodifiableIntByteMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableIntByteMap.access$000(this.this$0).iterator();
   }

    int key() {
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
