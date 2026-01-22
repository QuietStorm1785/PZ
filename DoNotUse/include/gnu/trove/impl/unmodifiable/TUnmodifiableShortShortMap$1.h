#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortShortIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortShortMap {
public:
    TShortShortIterator iter;

   TUnmodifiableShortShortMap$1(TUnmodifiableShortShortMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableShortShortMap.access$000(this.this$0).iterator();
   }

    short key() {
      return this.iter.key();
   }

    short value() {
      return this.iter.value();
   }

    void advance() {
      this.iter.advance();
   }

    bool hasNext() {
      return this.iter.hasNext();
   }

    short setValue(short val) {
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
