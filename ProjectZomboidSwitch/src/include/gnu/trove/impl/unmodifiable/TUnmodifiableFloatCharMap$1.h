#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TFloatCharIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatCharMap {
public:
    TFloatCharIterator iter;

   TUnmodifiableFloatCharMap$1(TUnmodifiableFloatCharMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableFloatCharMap.access$000(this.this$0).iterator();
   }

    float key() {
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
