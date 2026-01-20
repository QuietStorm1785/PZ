#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortIntIterator.h"

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortIntMap {
public:
    TShortIntIterator iter;

   TUnmodifiableShortIntMap$1(TUnmodifiableShortIntMap var1) {
      this.this$0 = var1;
      this.iter = TUnmodifiableShortIntMap.access$000(this.this$0).iterator();
   }

    short key() {
      return this.iter.key();
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
