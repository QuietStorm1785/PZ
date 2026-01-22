#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TCharShortIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharShortMap {
public:
    TCharShortIterator iter;

   TUnmodifiableCharShortMap$1(TUnmodifiableCharShortMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableCharShortMap.access$000(this.this$0).iterator();
   }

    char key() {
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
