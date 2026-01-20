#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TByteCharIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteCharMap {
public:
    TByteCharIterator iter;

   TUnmodifiableByteCharMap$1(TUnmodifiableByteCharMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableByteCharMap.access$000(this.this$0).iterator();
   }

    uint8_t key() {
      return this.iter.key();
   }

    char value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    char setValue(char val) {
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
