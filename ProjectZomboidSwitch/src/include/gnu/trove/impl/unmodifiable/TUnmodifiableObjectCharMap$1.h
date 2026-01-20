#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectCharIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectCharMap {
public:
   TObjectCharIterator<K> iter;

   TUnmodifiableObjectCharMap$1(TUnmodifiableObjectCharMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableObjectCharMap.access$000(this.this$0).iterator();
   }

    K key() {
      return (K)this.iter.key();
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
