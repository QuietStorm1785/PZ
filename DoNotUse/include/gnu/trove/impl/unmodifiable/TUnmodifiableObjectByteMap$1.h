#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectByteIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectByteMap {
public:
   TObjectByteIterator<K> iter;

   TUnmodifiableObjectByteMap$1(TUnmodifiableObjectByteMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableObjectByteMap.access$000(this.this$0).iterator();
   }

    K key() {
      return (K)this.iter.key();
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
