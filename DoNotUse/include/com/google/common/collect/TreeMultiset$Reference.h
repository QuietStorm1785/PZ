#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeMultiset {
public:
    T value;

   private TreeMultiset$Reference() {
   }

    T get() {
      return this.value;
   }

    void checkAndSet(@Nullable T, T newValue) {
      if (this.value != expected) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         this.value = newValue;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
