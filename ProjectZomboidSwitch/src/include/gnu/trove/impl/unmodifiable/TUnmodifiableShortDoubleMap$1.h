#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortDoubleIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortDoubleMap {
public:
    TShortDoubleIterator iter;

   TUnmodifiableShortDoubleMap$1(TUnmodifiableShortDoubleMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableShortDoubleMap.access$000(this.this$0).iterator();
   }

    short key() {
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
