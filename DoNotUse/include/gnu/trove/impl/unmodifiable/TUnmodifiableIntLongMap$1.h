#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TIntLongIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntLongMap {
public:
    TIntLongIterator iter;

   TUnmodifiableIntLongMap$1(TUnmodifiableIntLongMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableIntLongMap.access$000(this.this$0).iterator();
   }

    int key() {
      return this.iter.key();
   }

    long value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    long setValue(long val) {
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
