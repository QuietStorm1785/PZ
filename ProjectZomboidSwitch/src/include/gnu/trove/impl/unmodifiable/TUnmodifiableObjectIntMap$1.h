#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectIntIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectIntMap {
public:
   TObjectIntIterator<K> iter;

   TUnmodifiableObjectIntMap$1(TUnmodifiableObjectIntMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableObjectIntMap.access$000(this.this$0).iterator();
   }

    K key() {
      return (K)this.iter.key();
   }

    int value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    int setValue(int val) {
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
