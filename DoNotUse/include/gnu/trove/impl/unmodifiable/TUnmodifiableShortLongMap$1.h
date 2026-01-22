#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortLongIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortLongMap {
public:
    TShortLongIterator iter;

   TUnmodifiableShortLongMap$1(TUnmodifiableShortLongMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableShortLongMap.access$000(this.this$0).iterator();
   }

    short key() {
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
