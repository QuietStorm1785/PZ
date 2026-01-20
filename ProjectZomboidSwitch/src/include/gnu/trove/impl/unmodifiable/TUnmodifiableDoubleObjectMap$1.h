#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TDoubleObjectIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleObjectMap {
public:
   TDoubleObjectIterator<V> iter;

   TUnmodifiableDoubleObjectMap$1(TUnmodifiableDoubleObjectMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableDoubleObjectMap.access$000(this.this$0).iterator();
   }

    double key() {
      return this.iter.key();
   }

    V value() {
      return (V)this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    V setValue(V val) {
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
