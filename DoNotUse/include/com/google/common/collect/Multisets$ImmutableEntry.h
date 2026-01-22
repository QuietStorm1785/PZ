#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multisets/AbstractEntry.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
    const E element;
    const int count;
    static const long serialVersionUID = 0L;

   Multisets$ImmutableEntry(@Nullable E element, int count) {
      this.element = element;
      this.count = count;
      CollectPreconditions.checkNonnegative(count, "count");
   }

    E getElement() {
      return this.element;
   }

    int getCount() {
      return this.count;
   }

   public Multisets$ImmutableEntry<E> nextInBucket() {
    return nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
