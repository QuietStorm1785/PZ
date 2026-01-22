#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multisets/ImmutableEntry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableMultiset {
public:
   private const ImmutableEntry<E> nextInBucket;

   RegularImmutableMultiset$NonTerminalEntry(E element, int count, ImmutableEntry<E> nextInBucket) {
      super(element, count);
      this.nextInBucket = nextInBucket;
   }

   public ImmutableEntry<E> nextInBucket() {
      return this.nextInBucket;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
